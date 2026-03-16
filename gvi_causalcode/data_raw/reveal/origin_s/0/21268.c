static gboolean ng_file_seek_rand ( wtap * wth , gint64 offset , int * err , gchar * * err_info ) {
 ngsniffer_t * ngsniffer ;
 gint64 delta ;
 GList * new_list , * next_list ;
 blob_info_t * next_blob , * new_blob ;
 ngsniffer = ( ngsniffer_t * ) wth -> priv ;
 if ( wth -> file_type_subtype == WTAP_FILE_TYPE_SUBTYPE_NGSNIFFER_UNCOMPRESSED ) {
 if ( file_seek ( wth -> random_fh , offset , SEEK_SET , err ) == - 1 ) return FALSE ;
 return TRUE ;
 }
 delta = offset - ngsniffer -> rand . uncomp_offset ;
 new_list = NULL ;
 if ( delta > 0 ) {
 if ( ( size_t ) ( ngsniffer -> rand . nextout + delta ) >= ngsniffer -> rand . nbytes ) {
 if ( ngsniffer -> current_blob == NULL ) {
 new_list = ngsniffer -> first_blob ;
 }
 else {
 new_list = g_list_next ( ngsniffer -> current_blob ) ;
 }
 while ( new_list ) {
 next_list = g_list_next ( new_list ) ;
 if ( next_list == NULL ) {
 break ;
 }
 next_blob = ( blob_info_t * ) next_list -> data ;
 if ( next_blob -> blob_uncomp_offset > offset ) break ;
 new_list = next_list ;
 }
 if ( new_list == NULL ) {
 * err = WTAP_ERR_CANT_SEEK ;
 return FALSE ;
 }
 }
 }
 else if ( delta < 0 ) {
 if ( ngsniffer -> rand . nextout + delta < 0 ) {
 if ( ngsniffer -> current_blob == NULL ) {
 new_list = ngsniffer -> last_blob ;
 }
 else {
 new_list = g_list_previous ( ngsniffer -> current_blob ) ;
 }
 while ( new_list ) {
 new_blob = ( blob_info_t * ) new_list -> data ;
 if ( new_blob -> blob_uncomp_offset <= offset ) break ;
 new_list = g_list_previous ( new_list ) ;
 }
 if ( new_list == NULL ) {
 * err = WTAP_ERR_CANT_SEEK ;
 return FALSE ;
 }
 }
 }
 if ( new_list != NULL ) {
 new_blob = ( blob_info_t * ) new_list -> data ;
 if ( file_seek ( wth -> random_fh , new_blob -> blob_comp_offset , SEEK_SET , err ) == - 1 ) return FALSE ;
 if ( ngsniffer -> rand . buf == NULL ) {
 ngsniffer -> rand . buf = ( unsigned char * ) g_malloc ( OUTBUF_SIZE ) ;
 }
 ngsniffer -> current_blob = new_list ;
 ngsniffer -> rand . uncomp_offset = new_blob -> blob_uncomp_offset ;
 ngsniffer -> rand . comp_offset = new_blob -> blob_comp_offset ;
 if ( ! read_blob ( wth -> random_fh , & ngsniffer -> rand , err , err_info ) ) return FALSE ;
 delta = offset - ngsniffer -> rand . uncomp_offset ;
 g_assert ( delta >= 0 && ( unsigned long ) delta < ngsniffer -> rand . nbytes ) ;
 }
 ngsniffer -> rand . nextout += ( int ) delta ;
 ngsniffer -> rand . uncomp_offset += delta ;
 return TRUE ;
 }