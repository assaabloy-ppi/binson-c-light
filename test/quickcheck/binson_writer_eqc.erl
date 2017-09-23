-module(binson_writer_eqc).

%% include some quickcheck headers
-include_lib("eqc/include/eqc.hrl").
-include_lib("eqc/include/eqc_statem.hrl").

%% include the eqc-c generated header
-include("binson_light.hrl").

%% include binson defines
-include("binson_def.hrl").

-compile(export_all).

-define(BOUND8,  (1 bsl 7)).
-define(BOUND16, (1 bsl 15)).
-define(BOUND32, (1 bsl 31)).

%% Record defining state of QuickCheck model of binson writer
-record(state, {
    buf_size,
    buf_ptr,
    writer_ptr,
    data_counter
}).

%% Test writer function - perform N tests
test_writer(N) -> eqc:quickcheck(eqc:numtests(N, prop_writer())).

%% repeat faulty test for writer function
retest_writer() -> eqc:check(prop_writer()).

setup() ->
    %% Compile and load the binson_light C code with as an Erlang module 'binson_light'.
    eqc_c:start(binson_light, [{c_src, "../../binson_light.c"}, {cppflags, "-I ../../ -std=c99"}, {cflags,"-O2"}]).

prop_writer() ->
    case code:which(binson_light) of
        non_existing -> setup();
        _ -> ok
    end,
    ?FORALL(Cmds, commands(?MODULE),
        aggregate(command_names(Cmds),
            begin
                {H, S, Res} = run_commands(?MODULE, Cmds),
                case S#state.buf_ptr of
                    undefined -> ok;
                    Buf_ptr -> eqc_c:free(Buf_ptr)
                end,
                case S#state.writer_ptr of
                    undefined -> ok;
                    Writer_ptr -> eqc_c:free(Writer_ptr)
                end,
                eqc_statem:pretty_commands(?MODULE,
                                           Cmds,
                                           {H, S, Res},
                                           eqc:equals(Res, ok)
                                           )
            end)).


binson_writer_types() ->
   [
      binson_write_object_begin,
      binson_write_object_end,
      binson_write_array_begin,
      binson_write_array_end,
      binson_write_boolean,
      binson_write_integer,
      binson_write_double,
      binson_write_string,
      binson_write_name,
      binson_write_string_with_len,
      %binson_write_string_bbuf,
      binson_write_bytes
   ].

integer_gen() -> oneof([int(), largeint()]).
string_gen()  -> non_empty(list(choose($A, $Z))).
binary_gen()  -> eqc_gen:binary().

binson_arg_gen(binson_write_object_begin) -> [];
binson_arg_gen(binson_write_object_end)   -> [];
binson_arg_gen(binson_write_array_begin)  -> [];
binson_arg_gen(binson_write_array_end)    -> [];
binson_arg_gen(binson_write_boolean)      -> [eqc_gen:oneof([0,1])];
binson_arg_gen(binson_write_integer)      -> [integer_gen()];
binson_arg_gen(binson_write_double)       -> [eqc_gen:real()];
binson_arg_gen(binson_write_string)       -> [string_gen()];
binson_arg_gen(binson_write_name)         -> [string_gen()];
binson_arg_gen(binson_write_string_with_len) -> ?LET(Str, string_gen(), [Str, length(Str)]);
binson_arg_gen(binson_write_bytes)        -> ?LET(Bin, binary_gen(), [Bin, byte_size(Bin)]).

binson_encoder(binson_write_object_begin, []) -> <<?BEGIN_OBJ>>;
binson_encoder(binson_write_object_end, [])   -> <<?END_OBJ>>;
binson_encoder(binson_write_array_begin, [])  -> <<?BEGIN_ARR>>;
binson_encoder(binson_write_array_end, [])    -> <<?END_ARR>>;
binson_encoder(binson_write_boolean, [0])     -> <<?FALSE>>;
binson_encoder(binson_write_boolean, [1])     -> <<?TRUE>>;
binson_encoder(binson_write_integer, [Int])   ->
   if
      Int >= -?BOUND8  andalso Int < ?BOUND8  -> <<?INT8,  Int:8/integer-little>>;
      Int >= -?BOUND16 andalso Int < ?BOUND16 -> <<?INT16, Int:16/integer-little>>;
      Int >= -?BOUND32 andalso Int < ?BOUND32 -> <<?INT32, Int:32/integer-little>>;
      true                                    -> <<?INT64, Int:64/integer-little>>
   end;
binson_encoder(binson_write_double, [Float])  -> <<?DOUBLE, Float/float-little>>;
binson_encoder(binson_write_string, [String]) ->
   Binary = list_to_binary(String),
   Len = byte_size(Binary),
   if
      Len < 16#100   -> <<?STR_LEN8,  Len:8/integer-little,  Binary/binary>>;
      Len < 16#10000 -> <<?STR_LEN16, Len:16/integer-little, Binary/binary>>;
      true           -> <<?STR_LEN32, Len:32/integer-little, Binary/binary>>
   end;
binson_encoder(binson_write_name, [String]) -> binson_encoder(binson_write_string, [String]);
binson_encoder(binson_write_string_with_len, [String, _Len]) -> binson_encoder(binson_write_string, [String]);
binson_encoder(binson_write_bytes, [Bytes, _Len]) ->
   Len = byte_size(Bytes),
   if
      Len < 16#100   -> <<?BYTE_LEN8,  Len:8/integer-little,  Bytes/binary>>;
      Len < 16#10000 -> <<?BYTE_LEN16, Len:16/integer-little, Bytes/binary>>;
      true           -> <<?BYTE_LEN32, Len:32/integer-little, Bytes/binary>>
   end.

initial_state() -> #state{buf_size = 0, data_counter = 0}.

%------- binson alloc -------
binson_alloc_buf_pre(S) -> S#state.buf_size == 0.
binson_alloc_buf_args(_S) -> [?SUCHTHAT(X, eqc_gen:nat(), X>10)].
binson_alloc_buf(Buf_size) -> eqc_c:alloc({array, Buf_size, unsigned_char}).
binson_alloc_buf_post(_S, _A, {ptr, _, _}) -> true;
binson_alloc_buf_post(_S, _A, _R) -> false.
binson_alloc_buf_next(S, Buf_ptr, [Buf_size]) -> S#state{buf_size = Buf_size, buf_ptr = Buf_ptr}.

%------- binson binson_writer_init -------
binson_writer_init_pre(S) -> S#state.buf_size =/= 0 andalso S#state.writer_ptr == undefined.
binson_writer_init_args(S) -> [S#state.buf_ptr, S#state.buf_size].
binson_writer_init(Buf_ptr, Buf_size) ->
   {ptr, _, _} = Writer_ptr = eqc_c:alloc({struct, '_binson_writer'}),
   ok = binson_light:binson_writer_init(Writer_ptr, Buf_ptr, Buf_size),
   Writer_ptr.
binson_writer_init_post(_S, _A, Writer_ptr) ->
   Writer = eqc_c:deref(Writer_ptr),
   Writer#'_binson_writer'.error_flags == ?BINSON_ID_OK.
binson_writer_init_next(S, Writer_ptr, _A) ->
   S#state{writer_ptr = Writer_ptr}.

 %------- binson binson_writer_reset -------
 binson_writer_reset_pre(S) -> S#state.writer_ptr =/= undefined.
 binson_writer_reset_args(S) -> [S#state.writer_ptr].
 binson_writer_reset(Writer_ptr) ->
    ok = binson_light:binson_writer_reset(Writer_ptr).
 binson_writer_reset_post(S, _A, _R) ->
    Writer = eqc_c:deref(S#state.writer_ptr),
    Writer#'_binson_writer'.error_flags == ?BINSON_ID_OK.
 binson_writer_reset_next(S, _R, _A) -> S#state{data_counter = 0}.

%------- binson binson_writer_get_counter -------
binson_writer_get_counter_pre(S) -> S#state.writer_ptr =/= undefined.
binson_writer_get_counter_args(S) -> [S#state.writer_ptr].
binson_writer_get_counter(Writer_ptr) ->
   Writer = eqc_c:deref(Writer_ptr),
   IO = Writer#'_binson_writer'.io,
   IO#'_binson_io'.counter.
binson_writer_get_counter_post(S, _A, Counter) -> eq(S#state.data_counter, Counter).
binson_writer_get_counter_next(S, _R, _A) -> S.

%------- binson_write_* -------
binson_write_pre(S) -> S#state.writer_ptr =/= undefined.
binson_write_args(S) ->
   Type_Val = ?LET(Type, eqc_gen:oneof(binson_writer_types()), {Type, binson_arg_gen(Type)}),
   [S#state.writer_ptr, S#state.buf_ptr, S#state.data_counter, Type_Val].
binson_write_pre(S, [_Writer_ptr, _Buf_ptr, _Data_counter, {Gen_type, Gen_val}]) ->
   S#state.buf_size-S#state.data_counter >= byte_size(binson_encoder(Gen_type, Gen_val)).
binson_write(Writer_ptr, Buf_ptr, Data_counter, {Gen_type, Gen_val}) ->
   Pre_buf = lists:sublist(eqc_c:deref(Buf_ptr), Data_counter),
   %io:format("Apply: ~p~p~n", [Gen_type, Gen_val]),
   apply(binson_light, Gen_type, [Writer_ptr]++Gen_val),
   Pre_buf =/= lists:sublist(eqc_c:deref(Buf_ptr), Data_counter).
binson_write_post(_S, [Writer_ptr, Buf_ptr, Data_counter, {Gen_type, Gen_val}], Modified) ->
   Writer = eqc_c:deref(Writer_ptr),
   Added_data = binary:list_to_bin(lists:sublist(eqc_c:deref(Buf_ptr), Data_counter+1, byte_size(binson_encoder(Gen_type, Gen_val)))),
   Added_data == binson_encoder(Gen_type, Gen_val) andalso
   Modified == false andalso
   Writer#'_binson_writer'.error_flags == ?BINSON_ID_OK.
binson_write_next(S, _R, [_Writer_ptr, _Buf_ptr, _Data_counter, {Gen_type, Gen_val}]) ->
   S#state{data_counter = S#state.data_counter + byte_size(binson_encoder(Gen_type, Gen_val))}.

 %------- binson_write_* full-------
 binson_write_full_pre(_S) -> false.%S#state.writer_ptr =/= undefined.
 binson_write_full_args(S) ->
    Type_Val = ?LET(Type, eqc_gen:oneof(binson_writer_types()), {Type, binson_arg_gen(Type)}),
    [S#state.writer_ptr, S#state.buf_ptr, S#state.data_counter, Type_Val].
 binson_write_full_pre(S, [_Writer_ptr, _Buf_ptr, _Data_counter, {Gen_type, Gen_val}]) ->
    S#state.buf_size-S#state.data_counter < byte_size(binson_encoder(Gen_type, Gen_val)).
 binson_write_full(Writer_ptr, Buf_ptr, Data_counter, {Gen_type, Gen_val}) ->
    Pre_buf = lists:sublist(eqc_c:deref(Buf_ptr), Data_counter),
    %io:format("Apply: ~p~p~n", [Gen_type, Gen_val]),
    apply(binson_light, Gen_type, [Writer_ptr]++Gen_val),
    Pre_buf =/= lists:sublist(eqc_c:deref(Buf_ptr), Data_counter).
 binson_write_full_post(_S, [Writer_ptr, _Buf_ptr, _Data_counter, {_Gen_type, _Gen_val}], Modified) ->
    Writer = eqc_c:deref(Writer_ptr),
    Modified == false andalso
    Writer#'_binson_writer'.error_flags == ?BINSON_ID_BUF_FULL.
 binson_write_full_next(S, _R, [_Writer_ptr, _Buf_ptr, _Data_counter, {_Gen_type, _Gen_val}]) -> S.
