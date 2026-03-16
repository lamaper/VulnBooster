static void prplcb_request_action_free ( void * data ) {
 struct prplcb_request_action_data * pqad = data ;
 pqad -> bee_data = NULL ;
 purple_request_close ( PURPLE_REQUEST_ACTION , pqad ) ;
 }