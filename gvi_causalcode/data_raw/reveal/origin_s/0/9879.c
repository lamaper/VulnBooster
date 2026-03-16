static void message_decode_body_init_charset ( struct message_decoder_context * ctx , struct message_part * part ) {
 ctx -> binary_input = ctx -> content_charset == NULL && ( ctx -> flags & MESSAGE_DECODER_FLAG_RETURN_BINARY ) != 0 && ( part -> flags & ( MESSAGE_PART_FLAG_TEXT | MESSAGE_PART_FLAG_MESSAGE_RFC822 ) ) == 0 ;
 if ( ctx -> binary_input ) return ;
 if ( ctx -> charset_trans != NULL && ctx -> content_charset != NULL && strcasecmp ( ctx -> content_charset , ctx -> charset_trans_charset ) == 0 ) {
 charset_to_utf8_reset ( ctx -> charset_trans ) ;
 return ;
 }
 if ( ctx -> charset_trans != NULL ) charset_to_utf8_end ( & ctx -> charset_trans ) ;
 i_free_and_null ( ctx -> charset_trans_charset ) ;
 ctx -> charset_trans_charset = i_strdup ( ctx -> content_charset != NULL ? ctx -> content_charset : "UTF-8" ) ;
 if ( charset_to_utf8_begin ( ctx -> charset_trans_charset , ctx -> normalizer , & ctx -> charset_trans ) < 0 ) ctx -> charset_trans = charset_utf8_to_utf8_begin ( ctx -> normalizer ) ;
 }