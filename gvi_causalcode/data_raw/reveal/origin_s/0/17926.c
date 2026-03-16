bool message_search_more_decoded ( struct message_search_context * ctx , struct message_block * block ) {
 if ( block -> part != ctx -> prev_part ) {
 message_search_reset ( ctx ) ;
 ctx -> prev_part = block -> part ;
 }
 return message_search_more_decoded2 ( ctx , block ) ;
 }