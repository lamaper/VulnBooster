static void command_line_test ( const char * words ) {
 wordexp_t we ;
 int i ;
 int retval = wordexp ( words , & we , 0 ) ;
 printf ( "wordexp returned %d\n" , retval ) ;
 for ( i = 0 ;
 i < we . we_wordc ;
 i ++ ) printf ( "we_wordv[%d] = \"%s\"\n" , i , we . we_wordv [ i ] ) ;
 }