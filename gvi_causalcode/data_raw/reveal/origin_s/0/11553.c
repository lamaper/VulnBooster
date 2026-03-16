gboolean proto_is_frame_protocol ( const wmem_list_t * layers , const char * proto_name ) {
 wmem_list_frame_t * protos = wmem_list_head ( layers ) ;
 int proto_id ;
 const char * name ;
 while ( protos != NULL ) {
 proto_id = GPOINTER_TO_INT ( wmem_list_frame_data ( protos ) ) ;
 name = proto_get_protocol_filter_name ( proto_id ) ;
 if ( ! strcmp ( name , proto_name ) ) {
 return TRUE ;
 }
 protos = wmem_list_frame_next ( protos ) ;
 }
 return FALSE ;
 }