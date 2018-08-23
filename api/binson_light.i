/*  SWIG interface definitions */
%module binson

%include "stdint.i"
%include "typemaps.i"
%include exception.i

%{
#include "binson_light.h"
%}


/* ---- Common API specs for any target scripting language ---- */

%rename (BinsonWriter) _binson_writer;

%typemap(newfree) char * "free($1);";
%newobject *::toBytes();


%inline %{
void _checkError(binson_writer* bw) {
	int res = binson_writer_geterror(bw, 0xff);
	switch (res) {
		case BINSON_ID_INVALID_ARG:
			SWIG_exception(SWIG_RuntimeError, "Invalid argument specified");  break;
		case BINSON_ID_BUF_FULL:
			SWIG_exception(SWIG_RuntimeError, "Output buffer is full");  break;
	}
	thrown: ;
}
%}


typedef struct _binson_writer
{
};


%extend _binson_writer {

    _binson_writer(char *STRING, int LENGTH) {
    	binson_writer *bw;
    	bw = (binson_writer *) malloc(sizeof(binson_writer));
    	binson_writer_init(bw, STRING, LENGTH);
	    return bw;
    }
  	
  	~_binson_writer() {
    	free($self);
    }

	binson_writer* objectBegin() {
		binson_write_object_begin($self);
		return $self; /* allows method chaining */
	}

	binson_writer* objectEnd() {
		binson_write_object_end($self);
		return $self; /* allows method chaining */
	}

	binson_writer* arrayBegin() {
		binson_write_array_begin($self);
		return $self; /* allows method chaining */
	}

	binson_writer* arrayEnd() {
		binson_write_array_end($self);
		return $self; /* allows method chaining */
	}

	binson_writer* putBoolean(bool bval) {
		binson_write_boolean($self, bval);
		return $self; /* allows method chaining */
	}

	binson_writer* putTrue() {
		binson_write_boolean($self, true);
		return $self; /* allows method chaining */
	}

	binson_writer* putFalse() {
		binson_write_boolean($self, false);
		return $self; /* allows method chaining */
	}

	binson_writer* putInteger( int64_t ival ) {
		binson_write_integer($self, ival);
		return $self; /* allows method chaining */
	}

	binson_writer* putDouble( double dval ) {
		binson_write_double($self, dval);
		return $self; /* allows method chaining */
	}	

	binson_writer* putName(char *STRING, int LENGTH) {
		bbuf bb;
		bb.bptr = STRING;
		bb.bsize = LENGTH;

		binson_write_name_bbuf($self, &bb);
		return $self; /* allows method chaining */
	}	

	binson_writer* putString(char *STRING, int LENGTH) {
		bbuf bb;
		bb.bptr = STRING;
		bb.bsize = LENGTH;

		binson_write_string_bbuf($self, &bb);
		_checkError($self);

		return $self; /* allows method chaining */
	}	

	binson_writer* putBytes(char *STRING, int LENGTH) {
		bbuf bb;
		bb.bptr = STRING;
		bb.bsize = LENGTH;

		binson_write_bytes_bbuf($self, &bb);
		return $self; /* allows method chaining */
	}		

	binson_writer* putInline(binson_writer* sub_writer) {

		binson_write_raw($self, sub_writer->io.pbuf, sub_writer->io.buf_used);
		return $self; /* allows method chaining */
	}		


	int length() {
		return $self->io.buf_used;
	}

	int counter() {
		return binson_writer_get_counter($self);
	}

	char* toBytes() {
		int len = $self->io.buf_used;
		char *newstr = (char *) malloc(len+1);
		memcpy(newstr, $self->io.pbuf, len);
		newstr[len] = 0;
		return newstr;
	}

	//void serialize(void* obj) {
	//	SWIG_exception(SWIG_RuntimeError, "Not implemented");
	//	thrown:;
	//}

}


/* ---- Specific specs for some target scripting languages ---- */

#if defined(SWIGPHP) || defined(SWIGPHP7)
%include "binson_light_php.i"
#endif

#if defined(SWIGPYTHON)
%include "binson_light_python.i"
#endif

%import "../binson_light.h"
