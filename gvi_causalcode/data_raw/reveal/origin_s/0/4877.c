static int hfinfo_hex_digits ( const header_field_info * hfinfo ) {
 int bitwidth ;
 if ( hfinfo -> bitmask != 0 ) {
 bitwidth = hfinfo_mask_bitwidth ( hfinfo ) ;
 }
 else {
 bitwidth = hfinfo_type_bitwidth ( hfinfo -> type ) ;
 }
 return ( bitwidth + 3 ) / 4 ;
 }