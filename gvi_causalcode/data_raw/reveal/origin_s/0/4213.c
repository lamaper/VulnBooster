uint32 get_major_server_version ( ClusterInfo * cluster ) {
 FILE * version_fd ;
 char ver_filename [ MAXPGPATH ] ;
 int integer_version = 0 ;
 int fractional_version = 0 ;
 snprintf ( ver_filename , sizeof ( ver_filename ) , "%s/PG_VERSION" , cluster -> pgdata ) ;
 if ( ( version_fd = fopen ( ver_filename , "r" ) ) == NULL ) pg_fatal ( "could not open version file: %s\n" , ver_filename ) ;
 if ( fscanf ( version_fd , "%63s" , cluster -> major_version_str ) == 0 || sscanf ( cluster -> major_version_str , "%d.%d" , & integer_version , & fractional_version ) != 2 ) pg_fatal ( "could not get version from %s\n" , cluster -> pgdata ) ;
 fclose ( version_fd ) ;
 return ( 100 * integer_version + fractional_version ) * 100 ;
 }