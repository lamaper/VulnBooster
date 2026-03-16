static void xml_start_tag ( void * userData , const char * name , const char * * atts ) {
 struct xml_ctx * ctx = ( struct xml_ctx * ) userData ;
 const char * c = strchr ( name , ':' ) ;
 int old_namelen , new_len ;
 if ( c == NULL ) c = name ;
 else c ++ ;
 old_namelen = strlen ( ctx -> name ) ;
 new_len = old_namelen + strlen ( c ) + 2 ;
 if ( new_len > ctx -> len ) {
 ctx -> name = xrealloc ( ctx -> name , new_len ) ;
 ctx -> len = new_len ;
 }
 xsnprintf ( ctx -> name + old_namelen , ctx -> len - old_namelen , ".%s" , c ) ;
 free ( ctx -> cdata ) ;
 ctx -> cdata = NULL ;
 ctx -> userFunc ( ctx , 0 ) ;
 }