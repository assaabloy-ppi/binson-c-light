/*
 *  Copyright (c) 2015 ASSA ABLOY AB
 *
 *  This file is part of binson-c-light, BINSON serialization format library in C.
 *
 *  binson-c-light is free software; you can redistribute it and/or modify it under
 *  the terms of the GNU Lesser General Public License (LGPL) as published
 *  by the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  As a special exception, the Contributors give you permission to link
 *  this library with independent modules to produce an executable,
 *  regardless of the license terms of these independent modules, and to
 *  copy and distribute the resulting executable under terms of your choice,
 *  provided that you also meet, for each linked independent module, the
 *  terms and conditions of the license of that module. An independent
 *  module is a module which is not derived from or based on this library.
 *  If you modify this library, you must extend this exception to your
 *  version of the library.
 *
 *  binson-c-light is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 *  License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef BINSONLIGHTTESTSTREAM_H
#define BINSONLIGHTTESTSTREAM_H

#include "binson_light.h"

/*
Parses 'raw_chunk_size' bytes and serialize back to 'binson_writer'.
Return true, if input is equal to output
*/
bool binson_stream_test_start(binson_parser *p, binson_writer *w, int raw_chunk_size);

/*
Not implemented, always return false
*/
bool binson_stream_test_more(binson_parser *p, binson_writer *w, int raw_chunk_size);

#endif // BINSONLIGHTTESTSTREAM_H
