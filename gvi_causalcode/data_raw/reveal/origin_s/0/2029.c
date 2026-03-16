void printEachForward ( UBreakIterator * boundary , UChar * str ) {
 int32_t end ;
 int32_t start = ubrk_first ( boundary ) ;
 for ( end = ubrk_next ( boundary ) ;
 end != UBRK_DONE ;
 start = end , end = ubrk_next ( boundary ) ) {
 printTextRange ( str , start , end ) ;
 }
 }