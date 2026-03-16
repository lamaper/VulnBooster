static void mgcpDialedDigits ( gchar * signalStr , gchar * * dialedDigits ) {
 gchar * tmpStr ;
 gchar * resultStr ;
 gint i , j ;
 guint resultStrLen = 1 ;
 if ( signalStr == NULL ) return ;
 tmpStr = g_strdup ( signalStr ) ;
 for ( i = 0 ;
 tmpStr [ i ] ;
 i ++ ) {
 switch ( tmpStr [ i ] ) {
 case '0' : case '1' : case '2' : case '3' : case '4' : case '5' : case '6' : case '7' : case '8' : case '9' : case '#' : case '*' : resultStrLen ++ ;
 break ;
 default : tmpStr [ i ] = '?' ;
 break ;
 }
 }
 if ( resultStrLen == 1 ) {
 g_free ( tmpStr ) ;
 return ;
 }
 resultStr = ( gchar * ) g_malloc ( resultStrLen ) ;
 for ( i = 0 , j = 0 ;
 tmpStr [ i ] ;
 i ++ ) {
 if ( tmpStr [ i ] != '?' ) resultStr [ j ++ ] = tmpStr [ i ] ;
 }
 resultStr [ j ] = '\0' ;
 g_free ( * dialedDigits ) ;
 g_free ( tmpStr ) ;
 * dialedDigits = resultStr ;
 return ;
 }