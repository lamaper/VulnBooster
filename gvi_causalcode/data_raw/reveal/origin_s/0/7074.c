static void complete_window_nicks ( GList * * list , WINDOW_REC * window , const char * word , const char * nicksuffix ) {
 CHANNEL_REC * channel ;
 GList * tmplist ;
 GSList * tmp ;
 channel = CHANNEL ( window -> active ) ;
 if ( channel != NULL ) {
 tmplist = completion_channel_nicks ( channel , word , nicksuffix ) ;
 * list = completion_joinlist ( * list , tmplist ) ;
 }
 if ( nicksuffix != NULL ) {
 return ;
 }
 for ( tmp = window -> items ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 channel = CHANNEL ( tmp -> data ) ;
 if ( channel != NULL && tmp -> data != window -> active ) {
 tmplist = completion_channel_nicks ( channel , word , nicksuffix ) ;
 * list = completion_joinlist ( * list , tmplist ) ;
 }
 }
 }