static gboolean read_blob ( FILE_T infile , ngsniffer_comp_stream_t * comp_stream , int * err , gchar * * err_info ) {
 int in_len ;
 unsigned short blob_len ;
 gint16 blob_len_host ;
 gboolean uncompressed ;
 unsigned char * file_inbuf ;
 int out_len ;
 if ( ! wtap_read_bytes_or_eof ( infile , & blob_len , 2 , err , err_info ) ) return FALSE ;
 comp_stream -> comp_offset += 2 ;
 blob_len_host = pletoh16 ( & blob_len ) ;
 if ( blob_len_host < 0 ) {
 in_len = - blob_len_host ;
 uncompressed = TRUE ;
 }
 else {
 in_len = blob_len_host ;
 uncompressed = FALSE ;
 }
 file_inbuf = ( unsigned char * ) g_malloc ( INBUF_SIZE ) ;
 if ( ! wtap_read_bytes ( infile , file_inbuf , in_len , err , err_info ) ) {
 g_free ( file_inbuf ) ;
 return FALSE ;
 }
 comp_stream -> comp_offset += in_len ;
 if ( uncompressed ) {
 memcpy ( comp_stream -> buf , file_inbuf , in_len ) ;
 out_len = in_len ;
 }
 else {
 out_len = SnifferDecompress ( file_inbuf , in_len , comp_stream -> buf , OUTBUF_SIZE , err , err_info ) ;
 if ( out_len < 0 ) {
 g_free ( file_inbuf ) ;
 return FALSE ;
 }
 }
 g_free ( file_inbuf ) ;
 comp_stream -> nextout = 0 ;
 comp_stream -> nbytes = out_len ;
 return TRUE ;
 }