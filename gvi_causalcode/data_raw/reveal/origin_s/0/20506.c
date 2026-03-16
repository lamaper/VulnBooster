static void remove_new_subdir ( char * subdir , bool rmtopdir ) {
 char new_path [ MAXPGPATH ] ;
 prep_status ( "Deleting files from new %s" , subdir ) ;
 snprintf ( new_path , sizeof ( new_path ) , "%s/%s" , new_cluster . pgdata , subdir ) ;
 if ( ! rmtree ( new_path , rmtopdir ) ) pg_fatal ( "could not delete directory \"%s\"\n" , new_path ) ;
 check_ok ( ) ;
 }