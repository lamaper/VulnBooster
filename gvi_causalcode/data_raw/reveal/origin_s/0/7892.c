static void handle_remote_ls_ctx ( struct xml_ctx * ctx , int tag_closed ) {
 struct remote_ls_ctx * ls = ( struct remote_ls_ctx * ) ctx -> userData ;
 if ( tag_closed ) {
 if ( ! strcmp ( ctx -> name , DAV_PROPFIND_RESP ) && ls -> dentry_name ) {
 if ( ls -> dentry_flags & IS_DIR ) {
 str_end_url_with_slash ( ls -> dentry_name , & ls -> dentry_name ) ;
 if ( ls -> flags & PROCESS_DIRS ) {
 ls -> userFunc ( ls ) ;
 }
 if ( strcmp ( ls -> dentry_name , ls -> path ) && ls -> flags & RECURSIVE ) {
 remote_ls ( ls -> dentry_name , ls -> flags , ls -> userFunc , ls -> userData ) ;
 }
 }
 else if ( ls -> flags & PROCESS_FILES ) {
 ls -> userFunc ( ls ) ;
 }
 }
 else if ( ! strcmp ( ctx -> name , DAV_PROPFIND_NAME ) && ctx -> cdata ) {
 char * path = ctx -> cdata ;
 if ( * ctx -> cdata == 'h' ) {
 path = strstr ( path , "//" ) ;
 if ( path ) {
 path = strchr ( path + 2 , '/' ) ;
 }
 }
 if ( path ) {
 const char * url = repo -> url ;
 if ( repo -> path ) url = repo -> path ;
 if ( strncmp ( path , url , repo -> path_len ) ) error ( "Parsed path '%s' does not match url: '%s'" , path , url ) ;
 else {
 path += repo -> path_len ;
 ls -> dentry_name = xstrdup ( path ) ;
 }
 }
 }
 else if ( ! strcmp ( ctx -> name , DAV_PROPFIND_COLLECTION ) ) {
 ls -> dentry_flags |= IS_DIR ;
 }
 }
 else if ( ! strcmp ( ctx -> name , DAV_PROPFIND_RESP ) ) {
 free ( ls -> dentry_name ) ;
 ls -> dentry_name = NULL ;
 ls -> dentry_flags = 0 ;
 }
 }