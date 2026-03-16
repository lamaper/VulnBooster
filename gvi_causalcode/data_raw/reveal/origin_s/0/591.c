static void usage ( void ) {
 print_version ( ) ;
 puts ( ORACLE_WELCOME_COPYRIGHT_NOTICE ( "2000" ) ) ;
 puts ( "Dumping structure and contents of MySQL databases and tables." ) ;
 short_usage_sub ( stdout ) ;
 print_defaults ( "my" , load_default_groups ) ;
 puts ( "" ) ;
 my_print_help ( my_long_options ) ;
 my_print_variables ( my_long_options ) ;
 }