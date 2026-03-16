static int decode_cabac_intra_mb_type ( H264Context * h , int ctx_base , int intra_slice ) {
 uint8_t * state = & h -> cabac_state [ ctx_base ] ;
 int mb_type ;
 if ( intra_slice ) {
 int ctx = 0 ;
 if ( h -> left_type [ LTOP ] & ( MB_TYPE_INTRA16x16 | MB_TYPE_INTRA_PCM ) ) ctx ++ ;
 if ( h -> top_type & ( MB_TYPE_INTRA16x16 | MB_TYPE_INTRA_PCM ) ) ctx ++ ;
 if ( get_cabac_noinline ( & h -> cabac , & state [ ctx ] ) == 0 ) return 0 ;
 state += 2 ;
 }
 else {
 if ( get_cabac_noinline ( & h -> cabac , state ) == 0 ) return 0 ;
 }
 if ( get_cabac_terminate ( & h -> cabac ) ) return 25 ;
 mb_type = 1 ;
 mb_type += 12 * get_cabac_noinline ( & h -> cabac , & state [ 1 ] ) ;
 if ( get_cabac_noinline ( & h -> cabac , & state [ 2 ] ) ) mb_type += 4 + 4 * get_cabac_noinline ( & h -> cabac , & state [ 2 + intra_slice ] ) ;
 mb_type += 2 * get_cabac_noinline ( & h -> cabac , & state [ 3 + intra_slice ] ) ;
 mb_type += 1 * get_cabac_noinline ( & h -> cabac , & state [ 3 + 2 * intra_slice ] ) ;
 return mb_type ;
 }