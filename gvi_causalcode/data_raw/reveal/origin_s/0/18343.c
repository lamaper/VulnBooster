static int fts_build_tokenized ( struct fts_mail_build_context * ctx , const unsigned char * data , size_t size , bool last ) {
 struct mail_user * user = ctx -> update_ctx -> backend -> ns -> user ;
 const struct fts_language * lang ;
 int ret ;
 if ( ctx -> cur_user_lang != NULL ) {
 }
 else if ( ( ret = fts_detect_language ( ctx , data , size , last , & lang ) ) < 0 ) {
 return - 1 ;
 }
 else if ( ret == 0 ) {
 return 0 ;
 }
 else {
 fts_mail_build_ctx_set_lang ( ctx , fts_user_language_find ( user , lang ) ) ;
 if ( ctx -> pending_input -> used > 0 ) {
 if ( fts_build_add_tokens_with_filter ( ctx , ctx -> pending_input -> data , ctx -> pending_input -> used ) < 0 ) return - 1 ;
 buffer_set_used_size ( ctx -> pending_input , 0 ) ;
 }
 }
 if ( fts_build_add_tokens_with_filter ( ctx , data , size ) < 0 ) return - 1 ;
 if ( last ) {
 if ( fts_build_add_tokens_with_filter ( ctx , NULL , 0 ) < 0 ) return - 1 ;
 }
 return 0 ;
 }