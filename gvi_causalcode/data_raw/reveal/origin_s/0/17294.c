static void execve_shell ( const char * shellname , char * args [ ] , char * const envp [ ] ) {
 int err ;
 ( void ) execve ( shellname , ( char * * ) args , envp ) ;
 err = errno ;
 if ( access ( shellname , R_OK | X_OK ) == 0 ) {
 size_t n_args = 0 ;
 char * * targs ;
 while ( NULL != args [ n_args ] ) {
 n_args ++ ;
 }
 targs = ( char * * ) xmalloc ( ( n_args + 3 ) * sizeof ( args [ 0 ] ) ) ;
 targs [ 0 ] = "sh" ;
 targs [ 1 ] = "-" ;
 targs [ 2 ] = xstrdup ( shellname ) ;
 targs [ n_args + 2 ] = NULL ;
 while ( 1 != n_args ) {
 targs [ n_args + 1 ] = args [ n_args - 1 ] ;
 n_args -- ;
 }
 ( void ) execve ( SHELL , targs , envp ) ;
 }
 else {
 errno = err ;
 }
 }