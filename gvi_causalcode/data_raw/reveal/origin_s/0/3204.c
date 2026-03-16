static void fts_parse_mail_header ( struct fts_mail_build_context * ctx , const struct message_block * raw_block ) {
 const struct message_header_line * hdr = raw_block -> hdr ;
 if ( strcasecmp ( hdr -> name , "Content-Type" ) == 0 ) fts_build_parse_content_type ( ctx , hdr ) ;
 else if ( strcasecmp ( hdr -> name , "Content-Disposition" ) == 0 ) fts_build_parse_content_disposition ( ctx , hdr ) ;
 }