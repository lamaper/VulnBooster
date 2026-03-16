static int script_connect ( struct mail_user * user , const char * * path_r ) {
 const char * path ;
 int fd ;
 path = mail_user_plugin_getenv ( user , "fts_decoder" ) ;
 if ( path == NULL ) return - 1 ;
 if ( * path != '/' ) path = t_strconcat ( user -> set -> base_dir , "/" , path , NULL ) ;
 fd = net_connect_unix_with_retries ( path , 1000 ) ;
 if ( fd == - 1 ) i_error ( "net_connect_unix(%s) failed: %m" , path ) ;
 else net_set_nonblock ( fd , FALSE ) ;
 * path_r = path ;
 return fd ;
 }