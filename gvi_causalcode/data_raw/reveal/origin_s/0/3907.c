static gboolean ng_read_bytes_or_eof ( wtap * wth , void * buffer , unsigned int nbytes , gboolean is_random , int * err , gchar * * err_info ) {
 ngsniffer_t * ngsniffer ;
 FILE_T infile ;
 ngsniffer_comp_stream_t * comp_stream ;
 unsigned char * outbuffer = ( unsigned char * ) buffer ;
 blob_info_t * blob ;
 unsigned int bytes_to_copy ;
 unsigned int bytes_left ;
 ngsniffer = ( ngsniffer_t * ) wth -> priv ;
 if ( is_random ) {
 infile = wth -> random_fh ;
 comp_stream = & ngsniffer -> rand ;
 }
 else {
 infile = wth -> fh ;
 comp_stream = & ngsniffer -> seq ;
 }
 if ( wth -> file_type_subtype == WTAP_FILE_TYPE_SUBTYPE_NGSNIFFER_UNCOMPRESSED ) {
 if ( ! wtap_read_bytes_or_eof ( infile , buffer , nbytes , err , err_info ) ) return FALSE ;
 comp_stream -> uncomp_offset += nbytes ;
 comp_stream -> comp_offset += nbytes ;
 return TRUE ;
 }
 if ( comp_stream -> buf == NULL ) {
 comp_stream -> buf = ( unsigned char * ) g_malloc ( OUTBUF_SIZE ) ;
 if ( is_random ) {
 ngsniffer -> current_blob = ngsniffer -> first_blob ;
 }
 else {
 if ( wth -> random_fh != NULL ) {
 g_assert ( ngsniffer -> first_blob == NULL ) ;
 blob = g_new ( blob_info_t , 1 ) ;
 blob -> blob_comp_offset = comp_stream -> comp_offset ;
 blob -> blob_uncomp_offset = comp_stream -> uncomp_offset ;
 ngsniffer -> first_blob = g_list_append ( ngsniffer -> first_blob , blob ) ;
 ngsniffer -> last_blob = ngsniffer -> first_blob ;
 }
 }
 if ( ! read_blob ( infile , comp_stream , err , err_info ) ) return FALSE ;
 }
 while ( nbytes > 0 ) {
 bytes_left = comp_stream -> nbytes - comp_stream -> nextout ;
 if ( bytes_left == 0 ) {
 if ( is_random ) {
 ngsniffer -> current_blob = g_list_next ( ngsniffer -> current_blob ) ;
 if ( ! ngsniffer -> current_blob ) {
 * err = WTAP_ERR_CANT_SEEK ;
 return FALSE ;
 }
 }
 else {
 if ( wth -> random_fh != NULL ) {
 blob = g_new ( blob_info_t , 1 ) ;
 blob -> blob_comp_offset = comp_stream -> comp_offset ;
 blob -> blob_uncomp_offset = comp_stream -> uncomp_offset ;
 ngsniffer -> last_blob = g_list_append ( ngsniffer -> last_blob , blob ) ;
 }
 }
 if ( ! read_blob ( infile , comp_stream , err , err_info ) ) return FALSE ;
 bytes_left = comp_stream -> nbytes - comp_stream -> nextout ;
 }
 bytes_to_copy = nbytes ;
 if ( bytes_to_copy > bytes_left ) bytes_to_copy = bytes_left ;
 memcpy ( outbuffer , & comp_stream -> buf [ comp_stream -> nextout ] , bytes_to_copy ) ;
 nbytes -= bytes_to_copy ;
 outbuffer += bytes_to_copy ;
 comp_stream -> nextout += bytes_to_copy ;
 comp_stream -> uncomp_offset += bytes_to_copy ;
 }
 return TRUE ;
 }