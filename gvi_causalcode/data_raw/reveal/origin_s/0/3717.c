int zrestore ( i_ctx_t * i_ctx_p ) {
 alloc_save_t * asave ;
 int code = restore_check_save ( i_ctx_p , & asave ) ;
 if ( code < 0 ) return code ;
 return dorestore ( i_ctx_p , asave ) ;
 }