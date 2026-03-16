static void unescape ( FILE * file , char * pos , size_t length ) {
 char * tmp ;
 DBUG_ENTER ( "unescape" ) ;
 if ( ! ( tmp = ( char * ) my_malloc ( length * 2 + 1 , MYF ( MY_WME ) ) ) ) die ( EX_MYSQLERR , "Couldn't allocate memory" ) ;
 mysql_real_escape_string ( & mysql_connection , tmp , pos , ( ulong ) length ) ;
 fputc ( '\'' , file ) ;
 fputs ( tmp , file ) ;
 fputc ( '\'' , file ) ;
 check_io ( file ) ;
 my_free ( tmp ) ;
 DBUG_VOID_RETURN ;
 }