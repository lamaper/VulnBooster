static void copy_subdir_files ( char * subdir ) {
 char old_path [ MAXPGPATH ] ;
 char new_path [ MAXPGPATH ] ;
 remove_new_subdir ( subdir , true ) ;
 snprintf ( old_path , sizeof ( old_path ) , "%s/%s" , old_cluster . pgdata , subdir ) ;
 snprintf ( new_path , sizeof ( new_path ) , "%s/%s" , new_cluster . pgdata , subdir ) ;
 prep_status ( "Copying old %s to new server" , subdir ) ;
 exec_prog ( UTILITY_LOG_FILE , NULL , true , # ifndef WIN32 "cp -Rf \"%s\" \"%s\"" , # else "xcopy /e /y /q /r \"%s\" \"%s\\\"" , # endif old_path , new_path ) ;
 check_ok ( ) ;
 }