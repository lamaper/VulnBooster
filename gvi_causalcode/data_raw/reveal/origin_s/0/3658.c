static struct mswsp_ct * get_create_converstation_data ( packet_info * pinfo ) {
 struct mswsp_ct * ct = NULL ;
 conversation_t * conversation ;
 conversation = find_or_create_conversation ( pinfo ) ;
 if ( ! conversation ) {
 return NULL ;
 }
 ct = ( struct mswsp_ct * ) conversation_get_proto_data ( conversation , proto_mswsp ) ;
 if ( ! ct ) {
 ct = wmem_new ( wmem_file_scope ( ) , struct mswsp_ct ) ;
 ct -> GSL_message_data = NULL ;
 conversation_add_proto_data ( conversation , proto_mswsp , ct ) ;
 }
 return ct ;
 }