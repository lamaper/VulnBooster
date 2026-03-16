static void prplcb_debug_print ( PurpleDebugLevel level , const char * category , const char * arg_s ) {
 fprintf ( stderr , "DEBUG %s: %s" , category , arg_s ) ;
 }