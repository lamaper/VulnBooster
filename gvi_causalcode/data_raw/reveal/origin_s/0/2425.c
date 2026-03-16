static int hfinfo_container_bitwidth ( const header_field_info * hfinfo ) {
 if ( ! hfinfo -> bitmask ) {
 return 0 ;
 }
 if ( hfinfo -> type == FT_BOOLEAN ) {
 return hfinfo -> display ;
 }
 return hfinfo_type_bitwidth ( hfinfo -> type ) ;
 }