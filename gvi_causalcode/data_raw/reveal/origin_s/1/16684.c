static char * unescape_word ( struct Curl_easy * data , const char * inputbuff ) {
 char * newp ;
 char * dictp ;
 char * ptr ;
 int len ;
 char ch ;
 int olen = 0 ;
 newp = curl_easy_unescape ( data , inputbuff , 0 , & len ) ;
 if ( ! newp ) return NULL ;
 dictp = malloc ( ( ( size_t ) len ) * 2 + 1 ) ;
 if ( dictp ) {
 for ( ptr = newp ;
 ( ch = * ptr ) != 0 ;
 ptr ++ ) {
 if ( ( ch <= 32 ) || ( ch == 127 ) || ( ch == '\'' ) || ( ch == '\"' ) || ( ch == '\\' ) ) {
 dictp [ olen ++ ] = '\\' ;
 }
 dictp [ olen ++ ] = ch ;
 }
 dictp [ olen ] = 0 ;
 }
 free ( newp ) ;
 return dictp ;
 }