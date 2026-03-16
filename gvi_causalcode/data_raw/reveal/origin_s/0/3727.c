time_t curl_getdate ( const char * p , const time_t * now ) {
 time_t parsed = - 1 ;
 int rc = parsedate ( p , & parsed ) ;
 ( void ) now ;
 switch ( rc ) {
 case PARSEDATE_OK : case PARSEDATE_LATER : case PARSEDATE_SOONER : return parsed ;
 }
 return - 1 ;
 }