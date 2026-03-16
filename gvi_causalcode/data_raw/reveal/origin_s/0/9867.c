int c_main ( void ) {
 UBreakIterator * boundary ;
 char cStringToExamine [ ] = "Aaa bbb ccc. Ddd eee fff." ;
 UChar stringToExamine [ sizeof ( cStringToExamine ) + 1 ] ;
 UErrorCode status = U_ZERO_ERROR ;
 printf ( "\n\n" "C Boundary Analysis\n" "-------------------\n\n" ) ;
 printf ( "Examining: %s\n" , cStringToExamine ) ;
 u_uastrcpy ( stringToExamine , cStringToExamine ) ;
 boundary = ubrk_open ( UBRK_SENTENCE , "en_us" , stringToExamine , - 1 , & status ) ;
 if ( U_FAILURE ( status ) ) {
 printf ( "ubrk_open error: %s\n" , u_errorName ( status ) ) ;
 exit ( 1 ) ;
 }
 printf ( "\n----- Sentence Boundaries, forward: -----------\n" ) ;
 printEachForward ( boundary , stringToExamine ) ;
 printf ( "\n----- Sentence Boundaries, backward: ----------\n" ) ;
 printEachBackward ( boundary , stringToExamine ) ;
 ubrk_close ( boundary ) ;
 boundary = ubrk_open ( UBRK_WORD , "en_us" , stringToExamine , u_strlen ( stringToExamine ) , & status ) ;
 printf ( "\n----- Word Boundaries, forward: -----------\n" ) ;
 printEachForward ( boundary , stringToExamine ) ;
 printf ( "\n----- Word Boundaries, backward: ----------\n" ) ;
 printEachBackward ( boundary , stringToExamine ) ;
 printf ( "\n----- first: -------------\n" ) ;
 printFirst ( boundary , stringToExamine ) ;
 printf ( "\n----- last: --------------\n" ) ;
 printLast ( boundary , stringToExamine ) ;
 printf ( "\n----- at pos 10: ---------\n" ) ;
 printAt ( boundary , 10 , stringToExamine ) ;
 ubrk_close ( boundary ) ;
 printf ( "\nEnd of C boundary analysis\n" ) ;
 return 0 ;
 }