static void get_remote_object_list ( unsigned char parent ) {
 char path [ ] = "objects/XX/" ;
 static const char hex [ ] = "0123456789abcdef" ;
 unsigned int val = parent ;
 path [ 8 ] = hex [ val >> 4 ] ;
 path [ 9 ] = hex [ val & 0xf ] ;
 remote_dir_exists [ val ] = 0 ;
 remote_ls ( path , ( PROCESS_FILES | PROCESS_DIRS ) , process_ls_object , & val ) ;
 }