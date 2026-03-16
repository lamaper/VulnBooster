static int lang_compare_first_component ( const char * a , const char * b ) {
 unsigned int da , db ;
 const char * p ;
 p = strchr ( a , '-' ) ;
 da = p ? ( unsigned int ) ( p - a ) : strlen ( a ) ;
 p = strchr ( b , '-' ) ;
 db = p ? ( unsigned int ) ( p - b ) : strlen ( b ) ;
 return strncmp ( a , b , MAX ( da , db ) ) ;
 }