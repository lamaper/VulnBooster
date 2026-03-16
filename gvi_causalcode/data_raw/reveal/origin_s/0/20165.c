static int decode_cabac_mb_cbp_luma ( H264Context * h ) {
 int cbp_b , cbp_a , ctx , cbp = 0 ;
 cbp_a = h -> left_cbp ;
 cbp_b = h -> top_cbp ;
 ctx = ! ( cbp_a & 0x02 ) + 2 * ! ( cbp_b & 0x04 ) ;
 cbp += get_cabac_noinline ( & h -> cabac , & h -> cabac_state [ 73 + ctx ] ) ;
 ctx = ! ( cbp & 0x01 ) + 2 * ! ( cbp_b & 0x08 ) ;
 cbp += get_cabac_noinline ( & h -> cabac , & h -> cabac_state [ 73 + ctx ] ) << 1 ;
 ctx = ! ( cbp_a & 0x08 ) + 2 * ! ( cbp & 0x01 ) ;
 cbp += get_cabac_noinline ( & h -> cabac , & h -> cabac_state [ 73 + ctx ] ) << 2 ;
 ctx = ! ( cbp & 0x04 ) + 2 * ! ( cbp & 0x02 ) ;
 cbp += get_cabac_noinline ( & h -> cabac , & h -> cabac_state [ 73 + ctx ] ) << 3 ;
 return cbp ;
 }