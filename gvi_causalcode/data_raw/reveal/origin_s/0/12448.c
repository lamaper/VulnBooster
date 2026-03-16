static int fts_build_unstructured_header ( struct fts_mail_build_context * ctx , const struct message_header_line * hdr ) {
 const unsigned char * data = hdr -> full_value ;
 unsigned char * buf = NULL ;
 unsigned int i ;
 int ret ;
 for ( i = 0 ;
 i < hdr -> full_value_len ;
 i ++ ) {
 if ( data [ i ] == '\0' ) {
 if ( buf == NULL ) {
 buf = i_malloc ( hdr -> full_value_len ) ;
 memcpy ( buf , data , i ) ;
 data = buf ;
 }
 buf [ i ] = ' ' ;
 }
 else if ( buf != NULL ) {
 buf [ i ] = data [ i ] ;
 }
 }
 ret = fts_build_data ( ctx , data , hdr -> full_value_len , TRUE ) ;
 i_free ( buf ) ;
 return ret ;
 }