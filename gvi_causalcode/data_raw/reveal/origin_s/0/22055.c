static int decode_cabac_b_mb_sub_type ( H264Context * h ) {
 int type ;
 if ( ! get_cabac ( & h -> cabac , & h -> cabac_state [ 36 ] ) ) return 0 ;
 if ( ! get_cabac ( & h -> cabac , & h -> cabac_state [ 37 ] ) ) return 1 + get_cabac ( & h -> cabac , & h -> cabac_state [ 39 ] ) ;
 type = 3 ;
 if ( get_cabac ( & h -> cabac , & h -> cabac_state [ 38 ] ) ) {
 if ( get_cabac ( & h -> cabac , & h -> cabac_state [ 39 ] ) ) return 11 + get_cabac ( & h -> cabac , & h -> cabac_state [ 39 ] ) ;
 type += 4 ;
 }
 type += 2 * get_cabac ( & h -> cabac , & h -> cabac_state [ 39 ] ) ;
 type += get_cabac ( & h -> cabac , & h -> cabac_state [ 39 ] ) ;
 return type ;
 }