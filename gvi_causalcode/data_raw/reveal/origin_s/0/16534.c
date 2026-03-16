static int decode_cabac_p_mb_sub_type ( H264Context * h ) {
 if ( get_cabac ( & h -> cabac , & h -> cabac_state [ 21 ] ) ) return 0 ;
 if ( ! get_cabac ( & h -> cabac , & h -> cabac_state [ 22 ] ) ) return 1 ;
 if ( get_cabac ( & h -> cabac , & h -> cabac_state [ 23 ] ) ) return 2 ;
 return 3 ;
 }