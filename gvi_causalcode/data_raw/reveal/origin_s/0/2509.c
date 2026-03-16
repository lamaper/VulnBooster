static int fix_paths ( void ) {
 char buff [ FN_REFLEN ] , * pos ;
 DBUG_ENTER ( "fix_paths" ) ;
 convert_dirname ( mysql_home , mysql_home , NullS ) ;
 my_realpath ( mysql_home , mysql_home , MYF ( 0 ) ) ;
 pos = strend ( mysql_home ) ;
 if ( pos [ - 1 ] != FN_LIBCHAR ) {
 pos [ 0 ] = FN_LIBCHAR ;
 pos [ 1 ] = 0 ;
 }
 convert_dirname ( lc_messages_dir , lc_messages_dir , NullS ) ;
 convert_dirname ( mysql_real_data_home , mysql_real_data_home , NullS ) ;
 ( void ) my_load_path ( mysql_home , mysql_home , "" ) ;
 ( void ) my_load_path ( mysql_real_data_home , mysql_real_data_home , mysql_home ) ;
 ( void ) my_load_path ( pidfile_name , pidfile_name_ptr , mysql_real_data_home ) ;
 convert_dirname ( opt_plugin_dir , opt_plugin_dir_ptr ? opt_plugin_dir_ptr : get_relative_path ( PLUGINDIR ) , NullS ) ;
 ( void ) my_load_path ( opt_plugin_dir , opt_plugin_dir , mysql_home ) ;
 opt_plugin_dir_ptr = opt_plugin_dir ;
 pidfile_name_ptr = pidfile_name ;
 my_realpath ( mysql_unpacked_real_data_home , mysql_real_data_home , MYF ( 0 ) ) ;
 mysql_unpacked_real_data_home_len = ( int ) strlen ( mysql_unpacked_real_data_home ) ;
 if ( mysql_unpacked_real_data_home [ mysql_unpacked_real_data_home_len - 1 ] == FN_LIBCHAR ) -- mysql_unpacked_real_data_home_len ;
 char * sharedir = get_relative_path ( SHAREDIR ) ;
 if ( test_if_hard_path ( sharedir ) ) strmake_buf ( buff , sharedir ) ;
 else strxnmov ( buff , sizeof ( buff ) - 1 , mysql_home , sharedir , NullS ) ;
 convert_dirname ( buff , buff , NullS ) ;
 ( void ) my_load_path ( lc_messages_dir , lc_messages_dir , buff ) ;
 if ( charsets_dir ) strmake_buf ( mysql_charsets_dir , charsets_dir ) ;
 else strxnmov ( mysql_charsets_dir , sizeof ( mysql_charsets_dir ) - 1 , buff , CHARSET_DIR , NullS ) ;
 ( void ) my_load_path ( mysql_charsets_dir , mysql_charsets_dir , buff ) ;
 convert_dirname ( mysql_charsets_dir , mysql_charsets_dir , NullS ) ;
 charsets_dir = mysql_charsets_dir ;
 if ( init_tmpdir ( & mysql_tmpdir_list , opt_mysql_tmpdir ) ) DBUG_RETURN ( 1 ) ;
 if ( ! opt_mysql_tmpdir ) opt_mysql_tmpdir = mysql_tmpdir ;


 if ( * opt_secure_file_priv == 0 ) {
 my_free ( opt_secure_file_priv ) ;
 opt_secure_file_priv = 0 ;
 }
 else {
 if ( strlen ( opt_secure_file_priv ) >= FN_REFLEN ) opt_secure_file_priv [ FN_REFLEN - 1 ] = '\0' ;
 if ( my_realpath ( buff , opt_secure_file_priv , 0 ) ) {
 sql_print_warning ( "Failed to normalize the argument for --secure-file-priv." ) ;
 DBUG_RETURN ( 1 ) ;
 }
 char * secure_file_real_path = ( char * ) my_malloc ( FN_REFLEN , MYF ( MY_FAE ) ) ;
 convert_dirname ( secure_file_real_path , buff , NullS ) ;
 my_free ( opt_secure_file_priv ) ;
 opt_secure_file_priv = secure_file_real_path ;
 }
 }
 DBUG_RETURN ( 0 ) ;
 }