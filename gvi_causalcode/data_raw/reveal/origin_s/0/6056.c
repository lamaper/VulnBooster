static void skip ( struct vars * v ) {
 const chr * start = v -> now ;
 assert ( v -> cflags & REG_EXPANDED ) ;
 for ( ;
 ;
 ) {
 while ( ! ATEOS ( ) && iscspace ( * v -> now ) ) v -> now ++ ;
 if ( ATEOS ( ) || * v -> now != CHR ( '#' ) ) break ;
 assert ( NEXT1 ( '#' ) ) ;
 while ( ! ATEOS ( ) && * v -> now != CHR ( '\n' ) ) v -> now ++ ;
 }
 if ( v -> now != start ) NOTE ( REG_UNONPOSIX ) ;
 }