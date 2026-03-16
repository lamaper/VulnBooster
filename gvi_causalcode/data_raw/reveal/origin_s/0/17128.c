static void fill_label_boolean ( field_info * fi , gchar * label_str ) {
 char * p = label_str ;
 int bitfield_byte_length = 0 , bitwidth ;
 guint64 unshifted_value ;
 guint64 value ;
 header_field_info * hfinfo = fi -> hfinfo ;
 const true_false_string * tfstring = ( const true_false_string * ) & tfs_true_false ;
 if ( hfinfo -> strings ) {
 tfstring = ( const struct true_false_string * ) hfinfo -> strings ;
 }
 value = fvalue_get_uinteger64 ( & fi -> value ) ;
 if ( hfinfo -> bitmask ) {
 bitwidth = hfinfo_container_bitwidth ( hfinfo ) ;
 unshifted_value = value ;
 unshifted_value <<= hfinfo_bitshift ( hfinfo ) ;
 p = decode_bitfield_value ( label_str , unshifted_value , hfinfo -> bitmask , bitwidth ) ;
 bitfield_byte_length = ( int ) ( p - label_str ) ;
 }
 label_fill ( label_str , bitfield_byte_length , hfinfo , value ? tfstring -> true_string : tfstring -> false_string ) ;
 }