static bool search_header ( struct message_search_context * ctx , const struct message_header_line * hdr ) {
 static const unsigned char crlf [ 2 ] = {
 '\r' , '\n' }
 ;
 return str_find_more ( ctx -> str_find_ctx , ( const unsigned char * ) hdr -> name , hdr -> name_len ) || str_find_more ( ctx -> str_find_ctx , hdr -> middle , hdr -> middle_len ) || str_find_more ( ctx -> str_find_ctx , hdr -> full_value , hdr -> full_value_len ) || ( ! hdr -> no_newline && str_find_more ( ctx -> str_find_ctx , crlf , 2 ) ) ;
 }