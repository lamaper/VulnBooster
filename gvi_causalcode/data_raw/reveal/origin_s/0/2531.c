static void * prplcb_request_action ( const char * title , const char * primary , const char * secondary , int default_action , PurpleAccount * account , const char * who , PurpleConversation * conv , void * user_data , size_t action_count , va_list actions ) {
 struct prplcb_request_action_data * pqad ;
 int i ;
 char * q ;
 pqad = g_new0 ( struct prplcb_request_action_data , 1 ) ;
 for ( i = 0 ;
 i < action_count ;
 i ++ ) {
 char * caption ;
 void * fn ;
 caption = va_arg ( actions , char * ) ;
 fn = va_arg ( actions , void * ) ;
 if ( strstr ( caption , "Accept" ) || strstr ( caption , "OK" ) ) {
 pqad -> yes = fn ;
 pqad -> yes_i = i ;
 }
 else if ( strstr ( caption , "Reject" ) || strstr ( caption , "Cancel" ) ) {
 pqad -> no = fn ;
 pqad -> no_i = i ;
 }
 }
 pqad -> user_data = user_data ;
 q = g_strdup_printf ( "Request: %s\n\n%s\n\n%s" , title , primary , secondary ) ;
 pqad -> bee_data = query_add ( local_bee -> ui_data , purple_ic_by_pa ( account ) , q , prplcb_request_action_yes , prplcb_request_action_no , prplcb_request_action_free , pqad ) ;
 g_free ( q ) ;
 return pqad ;
 }