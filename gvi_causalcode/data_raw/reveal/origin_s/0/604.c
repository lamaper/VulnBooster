struct message_search_context * message_search_init ( const char * normalized_key_utf8 , normalizer_func_t * normalizer , enum message_search_flags flags ) {
 struct message_search_context * ctx ;
 i_assert ( * normalized_key_utf8 != '\0' ) ;
 ctx = i_new ( struct message_search_context , 1 ) ;
 ctx -> flags = flags ;
 ctx -> decoder = message_decoder_init ( normalizer , 0 ) ;
 ctx -> str_find_ctx = str_find_init ( default_pool , normalized_key_utf8 ) ;
 return ctx ;
 }