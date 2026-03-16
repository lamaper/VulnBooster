static int fts_detect_language ( struct fts_mail_build_context * ctx , const unsigned char * data , size_t size , bool last , const struct fts_language * * lang_r ) {
 struct mail_user * user = ctx -> update_ctx -> backend -> ns -> user ;
 struct fts_language_list * lang_list = fts_user_get_language_list ( user ) ;
 const struct fts_language * lang ;
 switch ( fts_language_detect ( lang_list , data , size , & lang ) ) {
 case FTS_LANGUAGE_RESULT_SHORT : buffer_append ( ctx -> pending_input , data , size ) ;
 if ( last ) {
 * lang_r = fts_language_list_get_first ( lang_list ) ;
 return 1 ;
 }
 return 0 ;
 case FTS_LANGUAGE_RESULT_UNKNOWN : * lang_r = fts_language_list_get_first ( lang_list ) ;
 return 1 ;
 case FTS_LANGUAGE_RESULT_OK : * lang_r = lang ;
 return 1 ;
 case FTS_LANGUAGE_RESULT_ERROR : return - 1 ;
 default : i_unreached ( ) ;
 }
 }