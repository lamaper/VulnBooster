static void free_h225_info ( gpointer p ) {
 h323_calls_info_t * tmp_h323info = ( h323_calls_info_t * ) p ;
 DUMP_PTR2 ( tmp_h323info -> guid ) ;
 g_free ( tmp_h323info -> guid ) ;
 if ( tmp_h323info -> h245_list ) {
 GList * list2 = g_list_first ( tmp_h323info -> h245_list ) ;
 while ( list2 ) {
 h245_address_t * h245_add = ( h245_address_t * ) list2 -> data ;
 g_free ( ( void * ) h245_add -> h245_address . data ) ;
 g_free ( list2 -> data ) ;
 list2 = g_list_next ( list2 ) ;
 }
 g_list_free ( tmp_h323info -> h245_list ) ;
 }
 g_free ( p ) ;
 }