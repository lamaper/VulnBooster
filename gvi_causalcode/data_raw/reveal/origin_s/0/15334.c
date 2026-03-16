static int hfinfo_mask_bitwidth ( const header_field_info * hfinfo ) {
 if ( ! hfinfo -> bitmask ) {
 return 0 ;
 }
 return ws_ilog2 ( hfinfo -> bitmask ) - ws_ctz ( hfinfo -> bitmask ) + 1 ;
 }