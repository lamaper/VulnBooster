static void astream_parse_header ( struct attachment_istream * astream , struct message_header_line * hdr ) {
 if ( ! hdr -> continued ) {
 stream_add_data ( astream , hdr -> name , hdr -> name_len ) ;
 stream_add_data ( astream , hdr -> middle , hdr -> middle_len ) ;
 }
 stream_add_data ( astream , hdr -> value , hdr -> value_len ) ;
 if ( ! hdr -> no_newline ) {
 if ( hdr -> crlf_newline ) stream_add_data ( astream , "\r\n" , 2 ) ;
 else stream_add_data ( astream , "\n" , 1 ) ;
 }
 if ( hdr -> continues ) {
 hdr -> use_full_value = TRUE ;
 return ;
 }
 if ( strcasecmp ( hdr -> name , "Content-Type" ) == 0 ) parse_content_type ( astream , hdr ) ;
 else if ( strcasecmp ( hdr -> name , "Content-Disposition" ) == 0 ) parse_content_disposition ( astream , hdr ) ;
 }