static void ngsniffer_sequential_close ( wtap * wth ) {
 ngsniffer_t * ngsniffer ;
 ngsniffer = ( ngsniffer_t * ) wth -> priv ;
 if ( ngsniffer -> seq . buf != NULL ) {
 g_free ( ngsniffer -> seq . buf ) ;
 ngsniffer -> seq . buf = NULL ;
 }
 }