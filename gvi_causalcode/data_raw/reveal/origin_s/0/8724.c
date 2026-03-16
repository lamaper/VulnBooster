static void prplcb_request_action_yes ( void * data ) {
 struct prplcb_request_action_data * pqad = data ;
 if ( pqad -> yes ) {
 pqad -> yes ( pqad -> user_data , pqad -> yes_i ) ;
 }
 }