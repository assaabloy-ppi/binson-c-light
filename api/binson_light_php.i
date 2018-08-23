

%extend _binson_writer {
    

  	int sgetData(int i, int j) {
    return i+j + $self->error_flags;
    }

}

// tostring
