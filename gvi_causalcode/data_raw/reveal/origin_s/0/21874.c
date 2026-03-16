void usage_exit ( ) {
 fprintf ( stderr , "Usage: %s <options> input_filename output_filename\n" , exec_name ) ;
 fprintf ( stderr , "Options:\n" ) ;
 arg_show_usage ( stderr , svc_args ) ;
 exit ( EXIT_FAILURE ) ;
 }