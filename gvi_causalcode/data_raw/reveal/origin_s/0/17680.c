static void get_dav_remote_heads ( void ) {
 remote_ls ( "refs/" , ( PROCESS_FILES | PROCESS_DIRS | RECURSIVE ) , process_ls_ref , NULL ) ;
 }