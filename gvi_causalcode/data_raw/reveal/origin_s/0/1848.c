static void free_iax2_info ( gpointer p ) {
 iax2_info_t * ii = ( iax2_info_t * ) p ;
 g_free ( ii ) ;
 }