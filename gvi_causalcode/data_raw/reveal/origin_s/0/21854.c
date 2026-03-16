static int fts_build_data ( struct fts_mail_build_context * ctx , const unsigned char * data , size_t size , bool last ) {
 if ( ( ctx -> update_ctx -> backend -> flags & FTS_BACKEND_FLAG_TOKENIZED_INPUT ) != 0 ) {
 return fts_build_tokenized ( ctx , data , size , last ) ;
 }
 else if ( ( ctx -> update_ctx -> backend -> flags & FTS_BACKEND_FLAG_BUILD_FULL_WORDS ) != 0 ) {
 return fts_build_full_words ( ctx , data , size , last ) ;
 }
 else {
 return fts_backend_update_build_more ( ctx -> update_ctx , data , size ) ;
 }
 }