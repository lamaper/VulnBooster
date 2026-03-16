static void dump_string ( const byte * p , size_t n , int delim ) {
 for ( ;
 n ;
 n -- , p ++ ) {
 if ( ( * p & 0x80 ) || iscntrl ( * p ) || * p == delim ) {
 if ( * p == '\n' ) log_printf ( "\\n" ) ;
 else if ( * p == '\r' ) log_printf ( "\\r" ) ;
 else if ( * p == '\f' ) log_printf ( "\\f" ) ;
 else if ( * p == '\v' ) log_printf ( "\\v" ) ;
 else if ( * p == '\b' ) log_printf ( "\\b" ) ;
 else if ( ! * p ) log_printf ( "\\0" ) ;
 else log_printf ( "\\x%02x" , * p ) ;
 }
 else log_printf ( "%c" , * p ) ;
 }
 }