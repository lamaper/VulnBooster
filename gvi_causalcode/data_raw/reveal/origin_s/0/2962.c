void printLast ( UBreakIterator * boundary , UChar * str ) {
 int32_t start ;
 int32_t end = ubrk_last ( boundary ) ;
 start = ubrk_previous ( boundary ) ;
 printTextRange ( str , start , end ) ;
 }