static void fts_build_parse_content_disposition ( struct fts_mail_build_context * ctx , const struct message_header_line * hdr ) {
 i_free ( ctx -> content_disposition ) ;
 ctx -> content_disposition = i_strndup ( hdr -> full_value , hdr -> full_value_len ) ;
 }