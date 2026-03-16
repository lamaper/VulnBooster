void message_search_reset ( struct message_search_context * ctx ) {
 ctx -> content_type_text = TRUE ;
 ctx -> prev_part = NULL ;
 str_find_reset ( ctx -> str_find_ctx ) ;
 message_decoder_decode_reset ( ctx -> decoder ) ;
 }