static void process_ls_object ( struct remote_ls_ctx * ls ) {
 unsigned int * parent = ( unsigned int * ) ls -> userData ;
 const char * path = ls -> dentry_name ;
 unsigned char sha1 [ 20 ] ;
 if ( ! strcmp ( ls -> path , ls -> dentry_name ) && ( ls -> flags & IS_DIR ) ) {
 remote_dir_exists [ * parent ] = 1 ;
 return ;
 }
 if ( ! skip_prefix ( path , "objects/" , & path ) || get_sha1_hex_from_objpath ( path , sha1 ) ) return ;
 one_remote_object ( sha1 ) ;
 }