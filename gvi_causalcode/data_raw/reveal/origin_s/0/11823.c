int mszipd_decompress ( struct mszipd_stream * zip , off_t out_bytes ) {
 register unsigned int bit_buffer ;
 register int bits_left ;
 unsigned char * i_ptr , * i_end ;
 int i , state , error ;
 if ( ! zip || ( out_bytes < 0 ) ) return MSPACK_ERR_ARGS ;
 if ( zip -> error ) return zip -> error ;
 i = zip -> o_end - zip -> o_ptr ;
 if ( ( off_t ) i > out_bytes ) i = ( int ) out_bytes ;
 if ( i ) {
 if ( zip -> sys -> write ( zip -> output , zip -> o_ptr , i ) != i ) {
 return zip -> error = MSPACK_ERR_WRITE ;
 }
 zip -> o_ptr += i ;
 out_bytes -= i ;
 }
 if ( out_bytes == 0 ) return MSPACK_ERR_OK ;
 while ( out_bytes > 0 ) {
 RESTORE_BITS ;
 i = bits_left & 7 ;
 REMOVE_BITS ( i ) ;
 state = 0 ;
 do {
 READ_BITS ( i , 8 ) ;
 if ( i == 'C' ) state = 1 ;
 else if ( ( state == 1 ) && ( i == 'K' ) ) state = 2 ;
 else state = 0 ;
 }
 while ( state != 2 ) ;
 zip -> window_posn = 0 ;
 zip -> bytes_output = 0 ;
 STORE_BITS ;
 if ( ( error = inflate ( zip ) ) ) {
 D ( ( "inflate error %d" , error ) ) if ( zip -> repair_mode ) {
 if ( zip -> bytes_output == 0 && zip -> window_posn > 0 ) {
 zip -> flush_window ( zip , zip -> window_posn ) ;
 }
 zip -> sys -> message ( NULL , "MSZIP error, %u bytes of data lost." , MSZIP_FRAME_SIZE - zip -> bytes_output ) ;
 for ( i = zip -> bytes_output ;
 i < MSZIP_FRAME_SIZE ;
 i ++ ) {
 zip -> window [ i ] = '\0' ;
 }
 zip -> bytes_output = MSZIP_FRAME_SIZE ;
 }
 else {
 return zip -> error = ( error > 0 ) ? error : MSPACK_ERR_DECRUNCH ;
 }
 }
 zip -> o_ptr = & zip -> window [ 0 ] ;
 zip -> o_end = & zip -> o_ptr [ zip -> bytes_output ] ;
 i = ( out_bytes < ( off_t ) zip -> bytes_output ) ? ( int ) out_bytes : zip -> bytes_output ;
 if ( zip -> sys -> write ( zip -> output , zip -> o_ptr , i ) != i ) {
 return zip -> error = MSPACK_ERR_WRITE ;
 }
 if ( ( error > 0 ) && zip -> repair_mode ) return error ;
 zip -> o_ptr += i ;
 out_bytes -= i ;
 }
 if ( out_bytes ) {
 D ( ( "bytes left to output" ) ) return zip -> error = MSPACK_ERR_DECRUNCH ;
 }
 return MSPACK_ERR_OK ;
 }