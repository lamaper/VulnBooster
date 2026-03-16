static gboolean ng_file_skip_seq ( wtap * wth , gint64 delta , int * err , gchar * * err_info ) {
 ngsniffer_t * ngsniffer ;
 char * buf ;
 unsigned int amount_to_read ;
 ngsniffer = ( ngsniffer_t * ) wth -> priv ;
 if ( wth -> file_type_subtype == WTAP_FILE_TYPE_SUBTYPE_NGSNIFFER_UNCOMPRESSED ) {
 ngsniffer -> seq . uncomp_offset += delta ;
 return file_skip ( wth -> fh , delta , err ) ;
 }
 g_assert ( delta >= 0 ) ;
 buf = ( char * ) g_malloc ( INBUF_SIZE ) ;
 while ( delta != 0 ) {
 if ( delta > INBUF_SIZE ) amount_to_read = INBUF_SIZE ;
 else amount_to_read = ( unsigned int ) delta ;
 if ( ! ng_read_bytes ( wth , buf , amount_to_read , FALSE , err , err_info ) ) {
 g_free ( buf ) ;
 return FALSE ;
 }
 delta -= amount_to_read ;
 }
 g_free ( buf ) ;
 return TRUE ;
 }