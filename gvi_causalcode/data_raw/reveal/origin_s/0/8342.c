static void slirp_smb_cleanup ( SlirpState * s ) {
 char cmd [ 128 ] ;
 int ret ;
 if ( s -> smb_dir [ 0 ] != '\0' ) {
 snprintf ( cmd , sizeof ( cmd ) , "rm -rf %s" , s -> smb_dir ) ;
 ret = system ( cmd ) ;
 if ( ret == - 1 || ! WIFEXITED ( ret ) ) {
 error_report ( "'%s' failed." , cmd ) ;
 }
 else if ( WEXITSTATUS ( ret ) ) {
 error_report ( "'%s' failed. Error code: %d" , cmd , WEXITSTATUS ( ret ) ) ;
 }
 s -> smb_dir [ 0 ] = '\0' ;
 }
 }