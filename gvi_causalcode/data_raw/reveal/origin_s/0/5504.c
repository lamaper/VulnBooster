static int decode_cabac_mb_intra4x4_pred_mode ( H264Context * h , int pred_mode ) {
 int mode = 0 ;
 if ( get_cabac ( & h -> cabac , & h -> cabac_state [ 68 ] ) ) return pred_mode ;
 mode += 1 * get_cabac ( & h -> cabac , & h -> cabac_state [ 69 ] ) ;
 mode += 2 * get_cabac ( & h -> cabac , & h -> cabac_state [ 69 ] ) ;
 mode += 4 * get_cabac ( & h -> cabac , & h -> cabac_state [ 69 ] ) ;
 return mode + ( mode >= pred_mode ) ;
 }