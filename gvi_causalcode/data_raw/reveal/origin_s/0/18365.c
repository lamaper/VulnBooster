static char * * create_argv_help ( const char * path , const char * command , const char * subcommand ) {
 char * * req_argv = NULL ;
 const char * program ;
 if ( subcommand == NULL ) req_argv = xcalloc ( 3 , sizeof ( char * ) ) ;
 else req_argv = xcalloc ( 4 , sizeof ( char * ) ) ;
 program = strrchr ( path , '/' ) ;
 if ( program == NULL ) program = path ;
 else program ++ ;
 req_argv [ 0 ] = xstrdup ( program ) ;
 req_argv [ 1 ] = xstrdup ( command ) ;
 if ( subcommand == NULL ) req_argv [ 2 ] = NULL ;
 else {
 req_argv [ 2 ] = xstrdup ( subcommand ) ;
 req_argv [ 3 ] = NULL ;
 }
 return req_argv ;
 }