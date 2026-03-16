static void xml_end_tag ( void * userData , const char * name ) {
 struct xml_ctx * ctx = ( struct xml_ctx * ) userData ;
 const char * c = strchr ( name , ':' ) ;
 char * ep ;
 ctx -> userFunc ( ctx , 1 ) ;
 if ( c == NULL ) c = name ;
 else c ++ ;
 ep = ctx -> name + strlen ( ctx -> name ) - strlen ( c ) - 1 ;
 * ep = 0 ;
 }