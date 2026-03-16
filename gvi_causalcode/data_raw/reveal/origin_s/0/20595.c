void printEachBackward ( UBreakIterator * boundary , UChar * str ) {
 int32_t start ;
 int32_t end = ubrk_last ( boundary ) ;
 for ( start = ubrk_previous ( boundary ) ;
 start != UBRK_DONE ;
 end = start , start = ubrk_previous ( boundary ) ) {
 printTextRange ( str , start , end ) ;
 }
 }