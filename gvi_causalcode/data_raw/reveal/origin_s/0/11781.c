static void ngsniffer_close ( wtap * wth ) {
 ngsniffer_t * ngsniffer ;
 ngsniffer = ( ngsniffer_t * ) wth -> priv ;
 if ( ngsniffer -> rand . buf != NULL ) g_free ( ngsniffer -> rand . buf ) ;
 if ( ngsniffer -> first_blob != NULL ) {
 g_list_foreach ( ngsniffer -> first_blob , free_blob , NULL ) ;
 g_list_free ( ngsniffer -> first_blob ) ;
 }
 }