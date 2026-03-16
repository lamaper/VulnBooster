static bool message_decode_header ( struct message_decoder_context * ctx , struct message_header_line * hdr , struct message_block * output ) {
 size_t value_len ;
 if ( hdr -> continues ) {
 hdr -> use_full_value = TRUE ;
 return FALSE ;
 }
 T_BEGIN {
 if ( hdr -> name_len == 12 && strcasecmp ( hdr -> name , "Content-Type" ) == 0 ) parse_content_type ( ctx , hdr ) ;
 if ( hdr -> name_len == 25 && strcasecmp ( hdr -> name , "Content-Transfer-Encoding" ) == 0 ) ctx -> message_cte = message_decoder_parse_cte ( hdr ) ;
 }
 T_END ;
 buffer_set_used_size ( ctx -> buf , 0 ) ;
 message_header_decode_utf8 ( hdr -> full_value , hdr -> full_value_len , ctx -> buf , ctx -> normalizer ) ;
 value_len = ctx -> buf -> used ;
 if ( ctx -> normalizer != NULL ) {
 ( void ) ctx -> normalizer ( hdr -> name , hdr -> name_len , ctx -> buf ) ;
 buffer_append_c ( ctx -> buf , '\0' ) ;
 }
 else {
 if ( ! uni_utf8_get_valid_data ( ( const unsigned char * ) hdr -> name , hdr -> name_len , ctx -> buf ) ) buffer_append_c ( ctx -> buf , '\0' ) ;
 }
 ctx -> hdr = * hdr ;
 ctx -> hdr . full_value = ctx -> buf -> data ;
 ctx -> hdr . full_value_len = value_len ;
 ctx -> hdr . value_len = 0 ;
 if ( ctx -> buf -> used != value_len ) {
 ctx -> hdr . name = CONST_PTR_OFFSET ( ctx -> buf -> data , ctx -> hdr . full_value_len ) ;
 ctx -> hdr . name_len = ctx -> buf -> used - 1 - value_len ;
 }
 output -> hdr = & ctx -> hdr ;
 return TRUE ;
 }