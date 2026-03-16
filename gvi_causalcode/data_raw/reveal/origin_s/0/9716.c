bool message_search_more ( struct message_search_context * ctx , struct message_block * raw_block ) {
 struct message_block decoded_block ;
 return message_search_more_get_decoded ( ctx , raw_block , & decoded_block ) ;
 }