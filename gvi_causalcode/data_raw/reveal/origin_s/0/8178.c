static sig_handler signal_handler ( int sig ) {
 fprintf ( stderr , "mysqltest got " SIGNAL_FMT "\n" , sig ) ;
 dump_backtrace ( ) ;
 fprintf ( stderr , "Writing a core file...\n" ) ;
 fflush ( stderr ) ;
 my_write_core ( sig ) ;

