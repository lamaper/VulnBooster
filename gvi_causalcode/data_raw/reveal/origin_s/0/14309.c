static void translation_buf_decode ( struct message_decoder_context * ctx , const unsigned char * * data , size_t * size ) {
 unsigned char trans_buf [ CHARSET_MAX_PENDING_BUF_SIZE + 1 ] ;
 size_t data_wanted , skip ;
 size_t trans_size , orig_size ;
 memcpy ( trans_buf , ctx -> translation_buf , ctx -> translation_size ) ;
 data_wanted = sizeof ( trans_buf ) - ctx -> translation_size ;
 if ( data_wanted > * size ) data_wanted = * size ;
 memcpy ( trans_buf + ctx -> translation_size , * data , data_wanted ) ;
 orig_size = trans_size = ctx -> translation_size + data_wanted ;
 ( void ) charset_to_utf8 ( ctx -> charset_trans , trans_buf , & trans_size , ctx -> buf2 ) ;
 if ( trans_size <= ctx -> translation_size ) {
 i_assert ( orig_size < CHARSET_MAX_PENDING_BUF_SIZE ) ;
 memcpy ( ctx -> translation_buf , trans_buf , orig_size ) ;
 ctx -> translation_size = orig_size ;
 * data += * size ;
 * size = 0 ;
 return ;
 }
 skip = trans_size - ctx -> translation_size ;
 i_assert ( * size >= skip ) ;
 * data += skip ;
 * size -= skip ;
 ctx -> translation_size = 0 ;
 }