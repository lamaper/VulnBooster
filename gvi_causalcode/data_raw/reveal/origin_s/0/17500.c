static int fts_build_add_tokens_with_filter ( struct fts_mail_build_context * ctx , const unsigned char * data , size_t size ) {
 struct fts_tokenizer * tokenizer = ctx -> cur_user_lang -> index_tokenizer ;
 struct fts_filter * filter = ctx -> cur_user_lang -> filter ;
 const char * token , * error ;
 int ret = 1 , ret2 ;
 while ( ret > 0 ) T_BEGIN {
 ret = ret2 = fts_tokenizer_next ( tokenizer , data , size , & token , & error ) ;
 if ( ret2 > 0 && filter != NULL ) ret2 = fts_filter_filter ( filter , & token , & error ) ;
 if ( ret2 < 0 ) i_error ( "fts: Couldn't create indexable tokens: %s" , error ) ;
 if ( ret2 > 0 ) {
 if ( fts_backend_update_build_more ( ctx -> update_ctx , ( const void * ) token , strlen ( token ) ) < 0 ) ret = - 1 ;
 }
 }
 T_END ;
 return ret ;
 }