int qtmd_decompress ( struct qtmd_stream * qtm , off_t out_bytes ) {
 unsigned int frame_todo , frame_end , window_posn , match_offset , range ;
 unsigned char * window , * i_ptr , * i_end , * runsrc , * rundest ;
 int i , j , selector , extra , sym , match_length ;
 unsigned short H , L , C , symf ;
 register unsigned int bit_buffer ;
 register unsigned char bits_left ;
 if ( ! qtm || ( out_bytes < 0 ) ) return MSPACK_ERR_ARGS ;
 if ( qtm -> error ) return qtm -> error ;
 i = qtm -> o_end - qtm -> o_ptr ;
 if ( ( off_t ) i > out_bytes ) i = ( int ) out_bytes ;
 if ( i ) {
 if ( qtm -> sys -> write ( qtm -> output , qtm -> o_ptr , i ) != i ) {
 return qtm -> error = MSPACK_ERR_WRITE ;
 }
 qtm -> o_ptr += i ;
 out_bytes -= i ;
 }
 if ( out_bytes == 0 ) return MSPACK_ERR_OK ;
 RESTORE_BITS ;
 window = qtm -> window ;
 window_posn = qtm -> window_posn ;
 frame_todo = qtm -> frame_todo ;
 H = qtm -> H ;
 L = qtm -> L ;
 C = qtm -> C ;
 while ( ( qtm -> o_end - qtm -> o_ptr ) < out_bytes ) {
 if ( ! qtm -> header_read ) {
 H = 0xFFFF ;
 L = 0 ;
 READ_BITS ( C , 16 ) ;
 qtm -> header_read = 1 ;
 }
 frame_end = window_posn + ( out_bytes - ( qtm -> o_end - qtm -> o_ptr ) ) ;
 if ( ( window_posn + frame_todo ) < frame_end ) {
 frame_end = window_posn + frame_todo ;
 }
 if ( frame_end > qtm -> window_size ) {
 frame_end = qtm -> window_size ;
 }
 while ( window_posn < frame_end ) {
 GET_SYMBOL ( qtm -> model7 , selector ) ;
 if ( selector < 4 ) {
 struct qtmd_model * mdl = ( selector == 0 ) ? & qtm -> model0 : ( ( selector == 1 ) ? & qtm -> model1 : ( ( selector == 2 ) ? & qtm -> model2 : & qtm -> model3 ) ) ;
 GET_SYMBOL ( ( * mdl ) , sym ) ;
 window [ window_posn ++ ] = sym ;
 frame_todo -- ;
 }
 else {
 switch ( selector ) {
 case 4 : GET_SYMBOL ( qtm -> model4 , sym ) ;
 READ_MANY_BITS ( extra , extra_bits [ sym ] ) ;
 match_offset = position_base [ sym ] + extra + 1 ;
 match_length = 3 ;
 break ;
 case 5 : GET_SYMBOL ( qtm -> model5 , sym ) ;
 READ_MANY_BITS ( extra , extra_bits [ sym ] ) ;
 match_offset = position_base [ sym ] + extra + 1 ;
 match_length = 4 ;
 break ;
 case 6 : GET_SYMBOL ( qtm -> model6len , sym ) ;
 READ_MANY_BITS ( extra , length_extra [ sym ] ) ;
 match_length = length_base [ sym ] + extra + 5 ;
 GET_SYMBOL ( qtm -> model6 , sym ) ;
 READ_MANY_BITS ( extra , extra_bits [ sym ] ) ;
 match_offset = position_base [ sym ] + extra + 1 ;
 break ;
 default : D ( ( "got %d from selector" , selector ) ) return qtm -> error = MSPACK_ERR_DECRUNCH ;
 }
 rundest = & window [ window_posn ] ;
 frame_todo -= match_length ;
 if ( ( window_posn + match_length ) > qtm -> window_size ) {
 i = qtm -> window_size - window_posn ;
 j = window_posn - match_offset ;
 while ( i -- ) * rundest ++ = window [ j ++ & ( qtm -> window_size - 1 ) ] ;
 i = ( & window [ qtm -> window_size ] - qtm -> o_ptr ) ;
 if ( i > out_bytes ) {
 D ( ( "during window-wrap match;
 %d bytes to flush but only need %d" , i , ( int ) out_bytes ) ) return qtm -> error = MSPACK_ERR_DECRUNCH ;
 }
 if ( qtm -> sys -> write ( qtm -> output , qtm -> o_ptr , i ) != i ) {
 return qtm -> error = MSPACK_ERR_WRITE ;
 }
 out_bytes -= i ;
 qtm -> o_ptr = & window [ 0 ] ;
 qtm -> o_end = & window [ 0 ] ;
 rundest = & window [ 0 ] ;
 i = match_length - ( qtm -> window_size - window_posn ) ;
 while ( i -- ) * rundest ++ = window [ j ++ & ( qtm -> window_size - 1 ) ] ;
 window_posn = window_posn + match_length - qtm -> window_size ;
 break ;
 }
 else {
 i = match_length ;
 if ( match_offset > window_posn ) {
 j = match_offset - window_posn ;
 if ( j > ( int ) qtm -> window_size ) {
 D ( ( "match offset beyond window boundaries" ) ) return qtm -> error = MSPACK_ERR_DECRUNCH ;
 }
 runsrc = & window [ qtm -> window_size - j ] ;
 if ( j < i ) {
 i -= j ;
 while ( j -- > 0 ) * rundest ++ = * runsrc ++ ;
 runsrc = window ;
 }
 while ( i -- > 0 ) * rundest ++ = * runsrc ++ ;
 }
 else {
 runsrc = rundest - match_offset ;
 while ( i -- > 0 ) * rundest ++ = * runsrc ++ ;
 }
 window_posn += match_length ;
 }
 }
 }
 qtm -> o_end = & window [ window_posn ] ;
 if ( frame_todo > QTM_FRAME_SIZE ) {
 D ( ( "overshot frame alignment" ) ) return qtm -> error = MSPACK_ERR_DECRUNCH ;
 }
 if ( frame_todo == 0 ) {
 if ( bits_left & 7 ) REMOVE_BITS ( bits_left & 7 ) ;
 do {
 READ_BITS ( i , 8 ) ;
 }
 while ( i != 0xFF ) ;
 qtm -> header_read = 0 ;
 frame_todo = QTM_FRAME_SIZE ;
 }
 if ( window_posn == qtm -> window_size ) {
 i = ( qtm -> o_end - qtm -> o_ptr ) ;
 if ( i >= out_bytes ) break ;
 if ( qtm -> sys -> write ( qtm -> output , qtm -> o_ptr , i ) != i ) {
 return qtm -> error = MSPACK_ERR_WRITE ;
 }
 out_bytes -= i ;
 qtm -> o_ptr = & window [ 0 ] ;
 qtm -> o_end = & window [ 0 ] ;
 window_posn = 0 ;
 }
 }
 if ( out_bytes ) {
 i = ( int ) out_bytes ;
 if ( qtm -> sys -> write ( qtm -> output , qtm -> o_ptr , i ) != i ) {
 return qtm -> error = MSPACK_ERR_WRITE ;
 }
 qtm -> o_ptr += i ;
 }
 STORE_BITS ;
 qtm -> window_posn = window_posn ;
 qtm -> frame_todo = frame_todo ;
 qtm -> H = H ;
 qtm -> L = L ;
 qtm -> C = C ;
 return MSPACK_ERR_OK ;
 }