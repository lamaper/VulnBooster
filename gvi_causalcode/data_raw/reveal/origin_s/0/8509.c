static void prplcb_close_request ( PurpleRequestType type , void * data ) {
 struct prplcb_request_action_data * pqad ;
 struct request_input_data * ri ;
 struct purple_data * pd ;
 if ( ! data ) {
 return ;
 }
 switch ( type ) {
 case PURPLE_REQUEST_ACTION : pqad = data ;
 if ( pqad -> bee_data ) {
 query_del ( local_bee -> ui_data , pqad -> bee_data ) ;
 }
 g_free ( pqad ) ;
 break ;
 case PURPLE_REQUEST_INPUT : ri = data ;
 pd = ri -> ic -> proto_data ;
 imcb_remove_buddy ( ri -> ic , ri -> buddy , NULL ) ;
 g_free ( ri -> buddy ) ;
 g_hash_table_remove ( pd -> input_requests , GUINT_TO_POINTER ( ri -> id ) ) ;
 break ;
 default : g_free ( data ) ;
 break ;
 }
 }