/*  SWIG interface definitions */
%module binson
%include "stdint.i"
%include "typemaps.i"

%{
#include "binson_light.h"
%}


/* ---- Common API specs for any target scripting language ---- */

%rename (BinsonWriter) _binson_writer;

%typemap(newfree) char * "free($1);";
%newobject *::toString();


//%inline %{

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

	binson_writer* boolean(bool bval) {
		binson_write_boolean($self, bval);
		return $self; /* allows method chaining */
	}

	binson_writer* trueValue() {
		binson_write_boolean($self, true);
		return $self; /* allows method chaining */
	}

	binson_writer* falseValue() {
		binson_write_boolean($self, false);
		return $self; /* allows method chaining */
	}

	binson_writer* integer( int64_t ival ) {
		binson_write_integer($self, ival);
		return $self; /* allows method chaining */
	}

	int length() {
		return $self->io.buf_used;
	}

	int counter() {
		return binson_writer_get_counter($self);
	}

	char* toString() {
		char *newstr = (char *) malloc($self->io.buf_used);
		strncpy(newstr, $self->io.pbuf, $self->io.buf_used);
		return newstr;
	}

}


/* ---- Specific specs for some target scripting languages ---- */

#if defined(SWIGPHP) || defined(SWIGPHP7)
%include "binson_light_php.i"
#endif

#if defined(SWIGPYTHON)
%include "binson_light_python.i"
#endif

%import "../binson_light.h"
