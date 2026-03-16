bool message_search_more_get_decoded ( struct message_search_context * ctx , struct message_block * raw_block , struct message_block * decoded_block_r ) {
 struct message_header_line * hdr = raw_block -> hdr ;
 struct message_block decoded_block ;
 i_zero ( decoded_block_r ) ;
 decoded_block_r -> part = raw_block -> part ;
 if ( raw_block -> part != ctx -> prev_part ) {
 message_search_reset ( ctx ) ;
 ctx -> prev_part = raw_block -> part ;
 if ( hdr == NULL ) {
 ctx -> content_type_text = FALSE ;
 }
 }
 if ( hdr != NULL ) {
 handle_header ( ctx , hdr ) ;
 if ( ( ctx -> flags & MESSAGE_SEARCH_FLAG_SKIP_HEADERS ) != 0 ) {
 if ( hdr -> name_len != 12 && hdr -> name_len != 25 ) return FALSE ;
 if ( strcasecmp ( hdr -> name , "Content-Type" ) != 0 && strcasecmp ( hdr -> name , "Content-Transfer-Encoding" ) != 0 ) return FALSE ;
 }
 }
 else {
 if ( ! ctx -> content_type_text ) return FALSE ;
 }
 if ( ! message_decoder_decode_next_block ( ctx -> decoder , raw_block , & decoded_block ) ) return FALSE ;
 if ( decoded_block . hdr != NULL && ( ctx -> flags & MESSAGE_SEARCH_FLAG_SKIP_HEADERS ) != 0 ) {
 return FALSE ;
 }
 * decoded_block_r = decoded_block ;
 return message_search_more_decoded2 ( ctx , & decoded_block ) ;
 }