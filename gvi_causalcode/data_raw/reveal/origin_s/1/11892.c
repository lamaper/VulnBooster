static hb_language_t * language_reference ( hb_language_t * l ) {
 hb_language_t * c = ( hb_language_t * ) calloc ( 1 , sizeof ( hb_language_t ) ) ;
 if ( unlikely ( ! c ) ) return NULL ;
 * c = * l ;
 return c ;
 }