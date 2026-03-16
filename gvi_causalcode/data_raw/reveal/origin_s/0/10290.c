static void short_usage_sub ( FILE * f ) {
 fprintf ( f , "Usage: %s [OPTIONS] database [tables]\n" , my_progname_short ) ;
 fprintf ( f , "OR %s [OPTIONS] --databases [OPTIONS] DB1 [DB2 DB3...]\n" , my_progname_short ) ;
 fprintf ( f , "OR %s [OPTIONS] --all-databases [OPTIONS]\n" , my_progname_short ) ;
 }