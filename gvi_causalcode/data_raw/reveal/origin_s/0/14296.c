void message_search_deinit ( struct message_search_context * * _ctx ) {
 struct message_search_context * ctx = * _ctx ;
 * _ctx = NULL ;
 str_find_deinit ( & ctx -> str_find_ctx ) ;
 message_decoder_deinit ( & ctx -> decoder ) ;
 i_free ( ctx ) ;
 }