void message_decoder_deinit ( struct message_decoder_context * * _ctx ) {
 struct message_decoder_context * ctx = * _ctx ;
 * _ctx = NULL ;
 if ( ctx -> charset_trans != NULL ) charset_to_utf8_end ( & ctx -> charset_trans ) ;
 if ( ctx -> qp != NULL ) qp_decoder_deinit ( & ctx -> qp ) ;
 buffer_free ( & ctx -> encoding_buf ) ;
 buffer_free ( & ctx -> buf ) ;
 buffer_free ( & ctx -> buf2 ) ;
 i_free ( ctx -> charset_trans_charset ) ;
 i_free ( ctx -> content_type ) ;
 i_free ( ctx -> content_charset ) ;
 i_free ( ctx ) ;
 }