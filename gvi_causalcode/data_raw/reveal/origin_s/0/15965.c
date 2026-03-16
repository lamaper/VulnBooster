static void handle_header ( struct message_search_context * ctx , struct message_header_line * hdr ) {
 if ( hdr -> name_len == 12 && strcasecmp ( hdr -> name , "Content-Type" ) == 0 ) {
 if ( hdr -> continues ) {
 hdr -> use_full_value = TRUE ;
 return ;
 }
 T_BEGIN {
 parse_content_type ( ctx , hdr ) ;
 }
 T_END ;
 }
 }