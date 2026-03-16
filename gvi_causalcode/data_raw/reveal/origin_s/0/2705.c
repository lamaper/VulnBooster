static int fts_build_body_block ( struct fts_mail_build_context * ctx , const struct message_block * block , bool last ) {
 i_assert ( block -> hdr == NULL ) ;
 return fts_build_data ( ctx , block -> data , block -> size , last ) ;
 }