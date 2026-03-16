static const char * ContentTypeForFilename ( const char * filename , const char * prevtype ) {
 const char * contenttype = NULL ;
 unsigned int i ;
 struct ContentType {
 const char * extension ;
 const char * type ;
 }
 ;
 static const struct ContentType ctts [ ] = {
 {
 ".gif" , "image/gif" }
 , {
 ".jpg" , "image/jpeg" }
 , {
 ".jpeg" , "image/jpeg" }
 , {
 ".txt" , "text/plain" }
 , {
 ".html" , "text/html" }
 , {
 ".xml" , "application/xml" }
 }
 ;
 if ( prevtype ) contenttype = prevtype ;
 else contenttype = HTTPPOST_CONTENTTYPE_DEFAULT ;
 if ( filename ) {
 for ( i = 0 ;
 i < sizeof ( ctts ) / sizeof ( ctts [ 0 ] ) ;
 i ++ ) {
 if ( strlen ( filename ) >= strlen ( ctts [ i ] . extension ) ) {
 if ( strequal ( filename + strlen ( filename ) - strlen ( ctts [ i ] . extension ) , ctts [ i ] . extension ) ) {
 contenttype = ctts [ i ] . type ;
 break ;
 }
 }
 }
 }
 return contenttype ;
 }