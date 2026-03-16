static int decode_cabac_mb_mvd ( H264Context * h , int ctxbase , int amvd , int * mvda ) {
 int mvd ;
 if ( ! get_cabac ( & h -> cabac , & h -> cabac_state [ ctxbase + ( ( amvd - 3 ) >> ( INT_BIT - 1 ) ) + ( ( amvd - 33 ) >> ( INT_BIT - 1 ) ) + 2 ] ) ) {
 * mvda = 0 ;
 return 0 ;
 }
 mvd = 1 ;
 ctxbase += 3 ;
 while ( mvd < 9 && get_cabac ( & h -> cabac , & h -> cabac_state [ ctxbase ] ) ) {
 if ( mvd < 4 ) ctxbase ++ ;
 mvd ++ ;
 }
 if ( mvd >= 9 ) {
 int k = 3 ;
 while ( get_cabac_bypass ( & h -> cabac ) ) {
 mvd += 1 << k ;
 k ++ ;
 if ( k > 24 ) {
 av_log ( h -> avctx , AV_LOG_ERROR , "overflow in decode_cabac_mb_mvd\n" ) ;
 return INT_MIN ;
 }
 }
 while ( k -- ) {
 mvd += get_cabac_bypass ( & h -> cabac ) << k ;
 }
 * mvda = mvd < 70 ? mvd : 70 ;
 }
 else * mvda = mvd ;
 return get_cabac_bypass_sign ( & h -> cabac , - mvd ) ;
 }