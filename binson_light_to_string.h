/*
 *  Copyright (c) 2017 APTUS AB
 *
 *  This file is part of binson-c-light, BINSON serialization format library in C.
 *
 *  License: MIT, Please see the file LICENSE for mor information
 */
#ifndef BINSONLIGHTTOSTRING_H
#define BINSONLIGHTTOSTRING_H
#include "binson_light.h"

/* Use a binson parser to output a human reable string describing the
	 binson stream. This is useful for debugging */
void binson_to_string(binson_parser *parser, char *str, int max_str_size);

#endif // BINSONLIGHTTOSTRING_H
