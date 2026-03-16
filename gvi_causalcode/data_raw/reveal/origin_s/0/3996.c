static void fts_build_tokenized_hdr_update_lang ( struct fts_mail_build_context * ctx , const struct message_header_line * hdr ) {
 if ( fts_header_has_language ( hdr -> name ) || data_has_8bit ( hdr -> full_value , hdr -> full_value_len ) ) ctx -> cur_user_lang = NULL ;
 else {
 fts_mail_build_ctx_set_lang ( ctx , fts_user_get_data_lang ( ctx -> update_ctx -> backend -> ns -> user ) ) ;
 }
 }