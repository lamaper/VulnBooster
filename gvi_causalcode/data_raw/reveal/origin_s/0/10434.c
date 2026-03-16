gboolean proto_can_toggle_protocol ( const int proto_id ) {
 protocol_t * protocol ;
 protocol = find_protocol_by_id ( proto_id ) ;
 return protocol -> can_toggle ;
 }