void hb_set_destroy ( hb_set_t * set ) {
 if ( ! hb_object_destroy ( set ) ) return ;
 set -> fini ( ) ;
 free ( set ) ;
 }