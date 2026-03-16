static mpa_state_t * get_mpa_state ( conversation_t * conversation ) {
 if ( conversation ) {
 return ( mpa_state_t * ) conversation_get_proto_data ( conversation , proto_iwarp_mpa ) ;
 }
 else {
 return NULL ;
 }
 }