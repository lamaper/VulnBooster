static gboolean capture_netbios ( const guchar * pd _U_ , int offset _U_ , int len _U_ , capture_packet_info_t * cpinfo , const union wtap_pseudo_header * pseudo_header _U_ ) {
 capture_dissector_increment_count ( cpinfo , proto_netbios ) ;
 return TRUE ;
 }