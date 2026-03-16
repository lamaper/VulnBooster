void check_eol_junk_line ( const char * line ) {
 const char * p = line ;
 DBUG_ENTER ( "check_eol_junk_line" ) ;
 DBUG_PRINT ( "enter" , ( "line: %s" , line ) ) ;
 if ( * p && ! strncmp ( p , delimiter , delimiter_length ) ) die ( "Extra delimiter \"%s\" found" , delimiter ) ;
 if ( * p && * p != '#' ) {
 if ( * p == '\n' ) die ( "Missing delimiter" ) ;
 die ( "End of line junk detected: \"%s\"" , p ) ;
 }
 DBUG_VOID_RETURN ;
 }