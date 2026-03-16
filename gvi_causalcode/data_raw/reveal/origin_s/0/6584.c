void check_cluster_versions ( void ) {
 prep_status ( "Checking cluster versions" ) ;
 old_cluster . major_version = get_major_server_version ( & old_cluster ) ;
 new_cluster . major_version = get_major_server_version ( & new_cluster ) ;
 if ( GET_MAJOR_VERSION ( old_cluster . major_version ) < 804 ) pg_fatal ( "This utility can only upgrade from PostgreSQL version 8.4 and later.\n" ) ;
 if ( GET_MAJOR_VERSION ( new_cluster . major_version ) != GET_MAJOR_VERSION ( PG_VERSION_NUM ) ) pg_fatal ( "This utility can only upgrade to PostgreSQL version %s.\n" , PG_MAJORVERSION ) ;
 if ( old_cluster . major_version > new_cluster . major_version ) pg_fatal ( "This utility cannot be used to downgrade to older major PostgreSQL versions.\n" ) ;
 get_bin_version ( & old_cluster ) ;
 get_bin_version ( & new_cluster ) ;
 if ( GET_MAJOR_VERSION ( old_cluster . major_version ) != GET_MAJOR_VERSION ( old_cluster . bin_version ) ) pg_fatal ( "Old cluster data and binary directories are from different major versions.\n" ) ;
 if ( GET_MAJOR_VERSION ( new_cluster . major_version ) != GET_MAJOR_VERSION ( new_cluster . bin_version ) ) pg_fatal ( "New cluster data and binary directories are from different major versions.\n" ) ;
 check_ok ( ) ;
 }