static int zip_read_lens ( struct mszipd_stream * zip ) {
 register unsigned int bit_buffer ;
 register int bits_left ;
 unsigned char * i_ptr , * i_end ;
 unsigned short bl_table [ ( 1 << 7 ) ] ;
 unsigned char bl_len [ 19 ] ;
 unsigned char lens [ MSZIP_LITERAL_MAXSYMBOLS + MSZIP_DISTANCE_MAXSYMBOLS ] ;
 unsigned int lit_codes , dist_codes , code , last_code = 0 , bitlen_codes , i , run ;
 RESTORE_BITS ;
 READ_BITS ( lit_codes , 5 ) ;
 lit_codes += 257 ;
 READ_BITS ( dist_codes , 5 ) ;
 dist_codes += 1 ;
 READ_BITS ( bitlen_codes , 4 ) ;
 bitlen_codes += 4 ;
 if ( lit_codes > MSZIP_LITERAL_MAXSYMBOLS ) return INF_ERR_SYMLENS ;
 if ( dist_codes > MSZIP_DISTANCE_MAXSYMBOLS ) return INF_ERR_SYMLENS ;
 for ( i = 0 ;
 i < bitlen_codes ;
 i ++ ) READ_BITS ( bl_len [ bitlen_order [ i ] ] , 3 ) ;
 while ( i < 19 ) bl_len [ bitlen_order [ i ++ ] ] = 0 ;
 if ( make_decode_table ( 19 , 7 , & bl_len [ 0 ] , & bl_table [ 0 ] ) ) {
 return INF_ERR_BITLENTBL ;
 }
 for ( i = 0 ;
 i < ( lit_codes + dist_codes ) ;
 i ++ ) {
 ENSURE_BITS ( 7 ) ;
 code = bl_table [ PEEK_BITS ( 7 ) ] ;
 REMOVE_BITS ( bl_len [ code ] ) ;
 if ( code < 16 ) lens [ i ] = last_code = code ;
 else {
 switch ( code ) {
 case 16 : READ_BITS ( run , 2 ) ;
 run += 3 ;
 code = last_code ;
 break ;
 case 17 : READ_BITS ( run , 3 ) ;
 run += 3 ;
 code = 0 ;
 break ;
 case 18 : READ_BITS ( run , 7 ) ;
 run += 11 ;
 code = 0 ;
 break ;
 default : D ( ( "bad code!: %u" , code ) ) return INF_ERR_BADBITLEN ;
 }
 if ( ( i + run ) > ( lit_codes + dist_codes ) ) return INF_ERR_BITOVERRUN ;
 while ( run -- ) lens [ i ++ ] = code ;
 i -- ;
 }
 }
 i = lit_codes ;
 zip -> sys -> copy ( & lens [ 0 ] , & zip -> LITERAL_len [ 0 ] , i ) ;
 while ( i < MSZIP_LITERAL_MAXSYMBOLS ) zip -> LITERAL_len [ i ++ ] = 0 ;
 i = dist_codes ;
 zip -> sys -> copy ( & lens [ lit_codes ] , & zip -> DISTANCE_len [ 0 ] , i ) ;
 while ( i < MSZIP_DISTANCE_MAXSYMBOLS ) zip -> DISTANCE_len [ i ++ ] = 0 ;
 STORE_BITS ;
 return 0 ;
 }