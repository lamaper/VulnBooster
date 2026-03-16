static void fts_mail_build_ctx_set_lang ( struct fts_mail_build_context * ctx , struct fts_user_language * user_lang ) {
 i_assert ( user_lang != NULL ) ;
 ctx -> cur_user_lang = user_lang ;
 fts_tokenizer_reset ( user_lang -> index_tokenizer ) ;
 }