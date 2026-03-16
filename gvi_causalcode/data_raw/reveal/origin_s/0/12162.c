static void * prplcb_notify_message ( PurpleNotifyMsgType type , const char * title , const char * primary , const char * secondary ) {
 char * text = g_strdup_printf ( "%s%s - %s%s%s" , ( type == PURPLE_NOTIFY_MSG_ERROR ) ? "Error: " : "" , title , primary ? : "" , ( primary && secondary ) ? " - " : "" , secondary ? : "" ) ;
 if ( local_bee -> ui -> log ) {
 local_bee -> ui -> log ( local_bee , "purple" , text ) ;
 }
 g_free ( text ) ;
 return NULL ;
 }