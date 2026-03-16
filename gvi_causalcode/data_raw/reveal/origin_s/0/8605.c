static void get_bin_version ( ClusterInfo * cluster ) {
 char cmd [ MAXPGPATH ] , cmd_output [ MAX_STRING ] ;
 FILE * output ;
 int pre_dot , post_dot ;
 snprintf ( cmd , sizeof ( cmd ) , "\"%s/pg_ctl\" --version" , cluster -> bindir ) ;
 if ( ( output = popen ( cmd , "r" ) ) == NULL || fgets ( cmd_output , sizeof ( cmd_output ) , output ) == NULL ) pg_fatal ( "Could not get pg_ctl version data using %s: %s\n" , cmd , getErrorText ( ) ) ;
 pclose ( output ) ;
 if ( strchr ( cmd_output , '\n' ) != NULL ) * strchr ( cmd_output , '\n' ) = '\0' ;
 if ( sscanf ( cmd_output , "%*s %*s %d.%d" , & pre_dot , & post_dot ) != 2 ) pg_fatal ( "could not get version from %s\n" , cmd ) ;
 cluster -> bin_version = ( pre_dot * 100 + post_dot ) * 100 ;
 }