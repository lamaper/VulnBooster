static void process_ls_ref ( struct remote_ls_ctx * ls ) {
 if ( ! strcmp ( ls -> path , ls -> dentry_name ) && ( ls -> dentry_flags & IS_DIR ) ) {
 fprintf ( stderr , " %s\n" , ls -> dentry_name ) ;
 return ;
 }
 if ( ! ( ls -> dentry_flags & IS_DIR ) ) one_remote_ref ( ls -> dentry_name ) ;
 }