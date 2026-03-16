static void mgcpCallerID ( gchar * signalStr , gchar * * callerId ) {
 gchar * * arrayStr ;
 if ( signalStr == NULL ) return ;
 arrayStr = g_strsplit ( signalStr , "\"" , 10 ) ;
 if ( arrayStr [ 0 ] == NULL ) return ;
 if ( strstr ( arrayStr [ 0 ] , "ci(" ) && ( arrayStr [ 1 ] != NULL ) ) {
 g_free ( * callerId ) ;
 * callerId = g_strdup ( arrayStr [ 1 ] ) ;
 }
 g_strfreev ( arrayStr ) ;
 return ;
 }