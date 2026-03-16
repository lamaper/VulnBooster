static gboolean isSignal ( const gchar * signal_str_p , const gchar * signalStr ) {
 gint i ;
 gchar * * resultArray ;
 if ( signalStr == NULL ) return FALSE ;
 if ( ( * signal_str_p == '\0' ) && ( * signalStr == '\0' ) ) return TRUE ;
 resultArray = g_strsplit ( signalStr , "," , 10 ) ;
 for ( i = 0 ;
 resultArray [ i ] ;
 i ++ ) {
 g_strstrip ( resultArray [ i ] ) ;
 if ( strcmp ( resultArray [ i ] , signal_str_p ) == 0 ) return TRUE ;
 }
 g_strfreev ( resultArray ) ;
 return FALSE ;
 }