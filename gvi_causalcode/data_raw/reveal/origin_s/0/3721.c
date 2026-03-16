static void prplcb_request_action_no ( void * data ) {
 struct prplcb_request_action_data * pqad = data ;
 if ( pqad -> no ) {
 pqad -> no ( pqad -> user_data , pqad -> no_i ) ;
 }
 }