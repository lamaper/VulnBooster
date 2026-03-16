void check_cluster_compatibility ( bool live_check ) {
 get_control_data ( & old_cluster , live_check ) ;
 get_control_data ( & new_cluster , false ) ;
 check_control_data ( & old_cluster . controldata , & new_cluster . controldata ) ;
 if ( GET_MAJOR_VERSION ( new_cluster . major_version ) == 900 && new_cluster . controldata . cat_ver < TABLE_SPACE_SUBDIRS_CAT_VER ) pg_fatal ( "This utility can only upgrade to PostgreSQL version 9.0 after 2010-01-11\n" "because of backend API changes made during development.\n" ) ;
 if ( live_check && GET_MAJOR_VERSION ( old_cluster . major_version ) < 901 && old_cluster . port == DEF_PGUPORT ) pg_fatal ( "When checking a pre-PG 9.1 live old server, " "you must specify the old server's port number.\n" ) ;
 if ( live_check && old_cluster . port == new_cluster . port ) pg_fatal ( "When checking a live server, " "the old and new port numbers must be different.\n" ) ;
 }