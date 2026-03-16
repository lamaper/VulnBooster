hb_set_t * hb_set_create ( void ) {
 hb_set_t * set ;
 if ( ! ( set = hb_object_create < hb_set_t > ( ) ) ) return hb_set_get_empty ( ) ;
 set -> clear ( ) ;
 return set ;
 }