int mszipd_decompress_kwaj ( struct mszipd_stream * zip ) {
 register unsigned int bit_buffer ;
 register int bits_left ;
 unsigned char * i_ptr , * i_end ;
 int i , error , block_len ;
 for ( ;
 ;
 ) {
 RESTORE_BITS ;
 i = bits_left & 7 ;
 REMOVE_BITS ( i ) ;
 READ_BITS ( block_len , 8 ) ;
 READ_BITS ( i , 8 ) ;
 block_len |= i << 8 ;
 if ( block_len == 0 ) break ;
 READ_BITS ( i , 8 ) ;
 if ( i != 'C' ) return MSPACK_ERR_DATAFORMAT ;
 READ_BITS ( i , 8 ) ;
 if ( i != 'K' ) return MSPACK_ERR_DATAFORMAT ;
 zip -> window_posn = 0 ;
 zip -> bytes_output = 0 ;
 STORE_BITS ;
 if ( ( error = inflate ( zip ) ) ) {
 D ( ( "inflate error %d" , error ) ) return zip -> error = ( error > 0 ) ? error : MSPACK_ERR_DECRUNCH ;
 }
 if ( zip -> sys -> write ( zip -> output , & zip -> window [ 0 ] , zip -> bytes_output ) != zip -> bytes_output ) return zip -> error = MSPACK_ERR_WRITE ;
 }
 return MSPACK_ERR_OK ;
 }