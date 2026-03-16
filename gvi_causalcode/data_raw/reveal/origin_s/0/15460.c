void proto_set_decoding ( const int proto_id , const gboolean enabled ) {
 protocol_t * protocol ;
 protocol = find_protocol_by_id ( proto_id ) ;
 DISSECTOR_ASSERT ( protocol -> can_toggle ) ;
 protocol -> is_enabled = enabled ;
 }