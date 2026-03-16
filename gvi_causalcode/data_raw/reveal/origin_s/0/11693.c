void purple_request_input_callback ( guint id , struct im_connection * ic , const char * message , const char * who ) {
 struct purple_data * pd = ic -> proto_data ;
 struct request_input_data * ri ;
 if ( ! ( ri = g_hash_table_lookup ( pd -> input_requests , GUINT_TO_POINTER ( id ) ) ) ) {
 return ;
 }
 ri -> data_callback ( ri -> user_data , message ) ;
 purple_request_close ( PURPLE_REQUEST_INPUT , ri ) ;
 }