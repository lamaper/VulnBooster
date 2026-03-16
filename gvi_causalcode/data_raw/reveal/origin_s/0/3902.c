static void process_response ( void * callback_data ) {
 struct transfer_request * request = ( struct transfer_request * ) callback_data ;
 finish_request ( request ) ;
 }