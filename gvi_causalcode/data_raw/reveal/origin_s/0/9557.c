int fts_build_mail ( struct fts_backend_update_context * update_ctx , struct mail * mail ) {
 int ret ;
 T_BEGIN {
 ret = fts_build_mail_real ( update_ctx , mail ) ;
 }
 T_END ;
 return ret ;
 }