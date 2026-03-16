static void ctl_putdata ( const char * dp , unsigned int dlen , int bin ) {
 int overhead ;
 unsigned int currentlen ;
 overhead = 0 ;
 if ( ! bin ) {
 datanotbinflag = TRUE ;
 overhead = 3 ;
 if ( datasent ) {
 * datapt ++ = ',' ;
 datalinelen ++ ;
 if ( ( dlen + datalinelen + 1 ) >= MAXDATALINELEN ) {
 * datapt ++ = '\r' ;
 * datapt ++ = '\n' ;
 datalinelen = 0 ;
 }
 else {
 * datapt ++ = ' ' ;
 datalinelen ++ ;
 }
 }
 }
 while ( dlen + overhead + datapt > dataend ) {
 currentlen = MIN ( dlen , ( unsigned int ) ( dataend - datapt ) ) ;
 memcpy ( datapt , dp , currentlen ) ;
 datapt += currentlen ;
 dp += currentlen ;
 dlen -= currentlen ;
 datalinelen += currentlen ;
 ctl_flushpkt ( CTL_MORE ) ;
 }
 memcpy ( datapt , dp , dlen ) ;
 datapt += dlen ;
 datalinelen += dlen ;
 datasent = TRUE ;
 }