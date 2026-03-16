static void search_stack_free ( void * key , void * data ) {
 ber_memfree_x ( data , NULL ) ;
 }