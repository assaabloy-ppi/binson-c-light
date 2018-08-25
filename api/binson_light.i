/*  SWIG interface definitions */
%module binson

%include "stdint.i"
%include "typemaps.i"
%include exception.i

%{
#include "binson_light.h"
%}


/* ==== Common API specs for any target scripting language  ==== */

%typemap(newfree) char * "free($1);";
%newobject *::toString();
%newobject *::toBytes();

%newobject *::getName();
%newobject *::getString();
%newobject *::getBytes();

#define BINSON_API_VERSION "binson_light-swig"


/* ---- BinsonWriter  ---- */

%rename (BinsonWriter) _binson_writer;

%inline %{
void _checkWriterError(binson_writer* bw) {
	int res = binson_writer_geterror(bw, 0xff);
	switch (res) {
		case BINSON_ID_OK:
			return;	
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
    	_checkWriterError(bw);
	    return bw;
    }
  	
  	~_binson_writer() {
    	free($self);
    }

	binson_writer* objectBegin() {
		binson_write_object_begin($self);
		_checkWriterError($self);
		return $self; /* allows method chaining */
	}

	binson_writer* objectEnd() {
		binson_write_object_end($self);
		_checkWriterError($self);
		return $self; /* allows method chaining */
	}

	binson_writer* arrayBegin() {
		binson_write_array_begin($self);
		_checkWriterError($self);
		return $self; /* allows method chaining */
	}

	binson_writer* arrayEnd() {
		binson_write_array_end($self);
		_checkWriterError($self);
		return $self; /* allows method chaining */
	}

	binson_writer* putBoolean(bool bval) {
		binson_write_boolean($self, bval);
		_checkWriterError($self);
		return $self; /* allows method chaining */
	}

	binson_writer* putTrue() {
		binson_write_boolean($self, true);
		_checkWriterError($self);
		return $self; /* allows method chaining */
	}

	binson_writer* putFalse() {
		binson_write_boolean($self, false);
		_checkWriterError($self);
		return $self; /* allows method chaining */
	}

	binson_writer* putInteger( int64_t ival ) {
		binson_write_integer($self, ival);
		_checkWriterError($self);
		return $self; /* allows method chaining */
	}

	binson_writer* putDouble( double dval ) {
		binson_write_double($self, dval);
		_checkWriterError($self);
		return $self; /* allows method chaining */
	}	

	binson_writer* putName(char *STRING, int LENGTH) {
		bbuf bb;
		bb.bptr = STRING;
		bb.bsize = LENGTH;

		binson_write_name_bbuf($self, &bb);
		_checkWriterError($self);
		return $self; /* allows method chaining */
	}	

	binson_writer* putString(char *STRING, int LENGTH) {
		bbuf bb;
		bb.bptr = STRING;
		bb.bsize = LENGTH;

		binson_write_string_bbuf($self, &bb);
		_checkWriterError($self);
		return $self; /* allows method chaining */
	}	

	binson_writer* putBytes(char *STRING, int LENGTH) {
		bbuf bb;
		bb.bptr = STRING;
		bb.bsize = LENGTH;

		binson_write_bytes_bbuf($self, &bb);
		_checkWriterError($self);
		return $self; /* allows method chaining */
	}		

	binson_writer* putInline(binson_writer* sub_writer) {

		binson_write_raw($self, sub_writer->io.pbuf, sub_writer->io.buf_used);
		_checkWriterError($self);
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

	// TODO
	//void serialize(void* obj) {
	//	SWIG_exception(SWIG_RuntimeError, "Not implemented");
	//	thrown:;
	//}

}

/* ---- BinsonParser  ---- */

%rename (BinsonParser) binson_parser;
%rename (at) _at;
%rename (field) _field;
%rename (next) _next;

%inline %{
void _checkParserError(binson_parser* bp) {
	int res = binson_parser_geterror(bp, 0xff);
	switch (res) {	
		case BINSON_ID_OK:
			return;
		case BINSON_ID_INVALID_ARG:
			SWIG_exception(SWIG_RuntimeError, "Invalid argument specified");  break;
		case BINSON_ID_BUF_FULL:
			SWIG_exception(SWIG_RuntimeError, "Output buffer is full");  break;
		case BINSON_ID_PARSE_NO_FIELD_NAME:
			SWIG_exception(SWIG_RuntimeError, "Requested field name not found");  break;
		case BINSON_ID_PARSE_BLOCK_ENDED:
			SWIG_exception(SWIG_RuntimeError, "End of block");  break;		
		case BINSON_ID_PARSE_WRONG_STATE:
			SWIG_exception(SWIG_RuntimeError, "Wrong parser state");  break;		
		case BINSON_ID_PARSE_WRONG_TYPE:
			SWIG_exception(SWIG_RuntimeError, "Wrong type");  break;		
		case BINSON_ID_PARSE_BAD_LEN:
			SWIG_exception(SWIG_RuntimeError, "Bad length field");  break;		
		case BINSON_ID_PARSE_END_OF_BUFFER:
			SWIG_exception(SWIG_RuntimeError, "End of buffer was reached");  break;		
		case BINSON_ID_PARSE_MAX_DEPTH_REACHED:
			SWIG_exception(SWIG_RuntimeError, "Nesting depth limit was reached. See MAX_DEPTH build-time constant");  break;
	}
	thrown: ;
}
%}


typedef struct binson_parser
{
};


%extend binson_parser {

    binson_parser(char *STRING, int LENGTH) {
    	binson_parser *bp;
    	bp = (binson_parser *) malloc(sizeof(binson_parser));
    	binson_parser_init(bp, STRING, LENGTH);
    	_checkParserError(bp);
	    return bp;
    }
  	
  	~binson_parser() {
    	free($self);
    }

    binson_parser* goInto()
    {
    	binson_parser_go_into($self);
    	_checkParserError($self);
    	return $self; /* allows method chaining */
    }
	
    binson_parser* goIntoObject()
    {
    	binson_parser_go_into_object($self);
    	_checkParserError($self);
    	return $self; /* allows method chaining */
    }

    binson_parser* goIntoArray()
    {
    	binson_parser_go_into_array($self);
    	_checkParserError($self);
    	return $self; /* allows method chaining */
    }

    binson_parser* goUp()
    {
    	binson_parser_go_up($self);
    	_checkParserError($self);
    	return $self; /* allows method chaining */
    }

    binson_parser* goUpToObject()
    {
    	binson_parser_go_upto_object($self);
    	_checkParserError($self);
    	return $self; /* allows method chaining */
    }

    binson_parser* goUpToArray()
    {
    	binson_parser_go_upto_array($self);
    	_checkParserError($self);
    	return $self; /* allows method chaining */
    }

    binson_parser* _at(uint8_t idx, uint8_t ensure_type = BINSON_ID_UNKNOWN)
    {
    	binson_parser_at_ensure($self, idx, ensure_type);
    	_checkParserError($self);
    	return $self; /* allows method chaining */
    }

    binson_parser* _field(const char *scan_name, uint8_t ensure_type = BINSON_ID_UNKNOWN)
    {
    	binson_parser_field_ensure($self, scan_name, ensure_type);
    	_checkParserError($self);
    	return $self; /* allows method chaining */
    }

    binson_parser* _next(uint8_t ensure_type = BINSON_ID_UNKNOWN)
    {
    	binson_parser_next_ensure($self, ensure_type);
    	_checkParserError($self);
    	return $self; /* allows method chaining */
    }

    /* extract current block being parsed raw bytes */
	char* toBytes() {
		bbuf bb;
		binson_parser_get_raw($self, &bb);
		_checkParserError($self);		

		char *newstr = (char *) malloc(bb.bsize);
		memcpy(newstr, bb.bptr, bb.bsize);
		return newstr;
	}

	bool getBoolean()
	{
		bool res = (bool)binson_parser_get_boolean($self);
		_checkParserError($self);
		return res;
	}

	int64_t getInteger()
	{
		int64_t res = binson_parser_get_integer($self);
		_checkParserError($self);
		return res;
	}

	double getDouble()
	{
		double res = binson_parser_get_double($self);
		_checkParserError($self);
		return res;
	}	

	char* getName()
	{
		bbuf *pbb = binson_parser_get_name_bbuf($self);
		char *newstr = (char *) malloc(pbb->bsize);
		memcpy(newstr, pbb->bptr, pbb->bsize);
		return newstr;
	}	

	char* getString()
	{
		bbuf *pbb = binson_parser_get_string_bbuf($self);
		char *newstr = (char *) malloc(pbb->bsize);
		memcpy(newstr, pbb->bptr, pbb->bsize);
		return newstr;
	}	

	char* getBytes()
	{
		bbuf *pbb = binson_parser_get_bytes_bbuf($self);
		char *newstr = (char *) malloc(pbb->bsize);
		memcpy(newstr, pbb->bptr, pbb->bsize);
		return newstr;
	}	
	

    uint8_t getDepth()
    {
    	return binson_parser_get_depth($self);
    }

    uint8_t getType()
    {
    	return binson_parser_get_type($self);
    }


%#ifdef WITH_TO_STRING
	char* toString(bool nice) {

		char *bigbuf = (char *) malloc(1024);
		char *newstr;
		bool res = binson_parser_to_string($self, bigbuf, 1024, nice);
		if (!res)
			bigbuf[0] = 0;

		int len = strlen(bigbuf);
		newstr = (char *) malloc(len+1);
		memcpy(newstr, bigbuf, len+1);

		free(bigbuf);
		return newstr;
	}
%#endif

	// TODO
	//void deserialize(void* obj) {
	//	SWIG_exception(SWIG_RuntimeError, "Not implemented");
	//	thrown:;
	//}

}


/*  ==== Specific specs for some target scripting languages  ==== */

#if defined(SWIGPHP) || defined(SWIGPHP7)
%include "binson_light_php.i"
#endif

#if defined(SWIGPYTHON)
%include "binson_light_python.i"
#endif

//%import "../binson_light.h"


%ignore ""; // Ignore everything from following includes
%rename("%s", %$isconstant) "";  // Unignoring constants

%include "../binson_light.h"
