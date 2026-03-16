static void voip_rtp_reset ( void * ptr _U_ ) {
 voip_rtp_tapinfo_t * tapinfo = & the_tapinfo_rtp_struct ;
 GList * list ;
 list = g_list_first ( tapinfo -> list ) ;
 while ( list ) {
 g_free ( list -> data ) ;
 list = g_list_next ( list ) ;
 }
 g_list_free ( tapinfo -> list ) ;
 tapinfo -> list = NULL ;
 tapinfo -> nstreams = 0 ;
 return ;
 }