static void parse_content_disposition ( struct attachment_istream * astream , const struct message_header_line * hdr ) {
 i_free ( astream -> part . content_disposition ) ;
 astream -> part . content_disposition = i_strndup ( hdr -> full_value , hdr -> full_value_len ) ;
 }