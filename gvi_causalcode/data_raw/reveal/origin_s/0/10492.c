static void usage ( int version ) {





 puts ( ORACLE_WELCOME_COPYRIGHT_NOTICE ( "2000" ) ) ;
 printf ( "Usage: %s [OPTIONS] [database]\n" , my_progname ) ;
 print_defaults ( "my" , load_default_groups ) ;
 puts ( "" ) ;
 my_print_help ( my_long_options ) ;
 my_print_variables ( my_long_options ) ;
 }