static int inflate ( struct mszipd_stream * zip ) {
 unsigned int last_block , block_type , distance , length , this_run , i ;
 register unsigned int bit_buffer ;
 register int bits_left ;
 register unsigned short sym ;
 unsigned char * i_ptr , * i_end ;
 RESTORE_BITS ;
 do {
 READ_BITS ( last_block , 1 ) ;
 READ_BITS ( block_type , 2 ) ;
 if ( block_type == 0 ) {
 unsigned char lens_buf [ 4 ] ;
 i = bits_left & 7 ;
 REMOVE_BITS ( i ) ;
 for ( i = 0 ;
 ( bits_left >= 8 ) ;
 i ++ ) {
 if ( i == 4 ) return INF_ERR_BITBUF ;
 lens_buf [ i ] = PEEK_BITS ( 8 ) ;
 REMOVE_BITS ( 8 ) ;
 }
 if ( bits_left != 0 ) return INF_ERR_BITBUF ;
 while ( i < 4 ) {
 READ_IF_NEEDED ;
 lens_buf [ i ++ ] = * i_ptr ++ ;
 }
 length = lens_buf [ 0 ] | ( lens_buf [ 1 ] << 8 ) ;
 i = lens_buf [ 2 ] | ( lens_buf [ 3 ] << 8 ) ;
 if ( length != ( ~ i & 0xFFFF ) ) return INF_ERR_COMPLEMENT ;
 while ( length > 0 ) {
 READ_IF_NEEDED ;
 this_run = length ;
 if ( this_run > ( unsigned int ) ( i_end - i_ptr ) ) this_run = i_end - i_ptr ;
 if ( this_run > ( MSZIP_FRAME_SIZE - zip -> window_posn ) ) this_run = MSZIP_FRAME_SIZE - zip -> window_posn ;
 zip -> sys -> copy ( i_ptr , & zip -> window [ zip -> window_posn ] , this_run ) ;
 zip -> window_posn += this_run ;
 i_ptr += this_run ;
 length -= this_run ;
 FLUSH_IF_NEEDED ;
 }
 }
 else if ( ( block_type == 1 ) || ( block_type == 2 ) ) {
 unsigned int match_posn , code ;
 if ( block_type == 1 ) {
 i = 0 ;
 while ( i < 144 ) zip -> LITERAL_len [ i ++ ] = 8 ;
 while ( i < 256 ) zip -> LITERAL_len [ i ++ ] = 9 ;
 while ( i < 280 ) zip -> LITERAL_len [ i ++ ] = 7 ;
 while ( i < 288 ) zip -> LITERAL_len [ i ++ ] = 8 ;
 for ( i = 0 ;
 i < 32 ;
 i ++ ) zip -> DISTANCE_len [ i ] = 5 ;
 }
 else {
 STORE_BITS ;
 if ( ( i = zip_read_lens ( zip ) ) ) return i ;
 RESTORE_BITS ;
 }
 if ( make_decode_table ( MSZIP_LITERAL_MAXSYMBOLS , MSZIP_LITERAL_TABLEBITS , & zip -> LITERAL_len [ 0 ] , & zip -> LITERAL_table [ 0 ] ) ) {
 return INF_ERR_LITERALTBL ;
 }
 if ( make_decode_table ( MSZIP_DISTANCE_MAXSYMBOLS , MSZIP_DISTANCE_TABLEBITS , & zip -> DISTANCE_len [ 0 ] , & zip -> DISTANCE_table [ 0 ] ) ) {
 return INF_ERR_DISTANCETBL ;
 }
 for ( ;
 ;
 ) {
 READ_HUFFSYM ( LITERAL , code ) ;
 if ( code < 256 ) {
 zip -> window [ zip -> window_posn ++ ] = ( unsigned char ) code ;
 FLUSH_IF_NEEDED ;
 }
 else if ( code == 256 ) {
 break ;
 }
 else {
 code -= 257 ;
 if ( code >= 29 ) return INF_ERR_LITCODE ;
 READ_BITS_T ( length , lit_extrabits [ code ] ) ;
 length += lit_lengths [ code ] ;
 READ_HUFFSYM ( DISTANCE , code ) ;
 if ( code >= 30 ) return INF_ERR_DISTCODE ;
 READ_BITS_T ( distance , dist_extrabits [ code ] ) ;
 distance += dist_offsets [ code ] ;
 match_posn = ( ( distance > zip -> window_posn ) ? MSZIP_FRAME_SIZE : 0 ) + zip -> window_posn - distance ;
 if ( length < 12 ) {
 while ( length -- ) {
 zip -> window [ zip -> window_posn ++ ] = zip -> window [ match_posn ++ ] ;
 match_posn &= MSZIP_FRAME_SIZE - 1 ;
 FLUSH_IF_NEEDED ;
 }
 }
 else {
 unsigned char * runsrc , * rundest ;
 do {
 this_run = length ;
 if ( ( match_posn + this_run ) > MSZIP_FRAME_SIZE ) this_run = MSZIP_FRAME_SIZE - match_posn ;
 if ( ( zip -> window_posn + this_run ) > MSZIP_FRAME_SIZE ) this_run = MSZIP_FRAME_SIZE - zip -> window_posn ;
 rundest = & zip -> window [ zip -> window_posn ] ;
 zip -> window_posn += this_run ;
 runsrc = & zip -> window [ match_posn ] ;
 match_posn += this_run ;
 length -= this_run ;
 while ( this_run -- ) * rundest ++ = * runsrc ++ ;
 if ( match_posn == MSZIP_FRAME_SIZE ) match_posn = 0 ;
 FLUSH_IF_NEEDED ;
 }
 while ( length > 0 ) ;
 }
 }
 }
 }
 else {
 return INF_ERR_BLOCKTYPE ;
 }
 }
 while ( ! last_block ) ;
 if ( zip -> window_posn ) {
 if ( zip -> flush_window ( zip , zip -> window_posn ) ) return INF_ERR_FLUSH ;
 }
 STORE_BITS ;
 return 0 ;
 }