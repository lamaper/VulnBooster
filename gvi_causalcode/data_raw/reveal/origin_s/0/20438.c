static const gchar * gen_olc_key ( guint16 lc_num , address * dst_addr , address * src_addr ) {
 return wmem_strdup_printf ( wmem_packet_scope ( ) , "%s/%s/%u" , address_to_str ( wmem_packet_scope ( ) , dst_addr ) , address_to_str ( wmem_packet_scope ( ) , src_addr ) , lc_num ) ;
 }