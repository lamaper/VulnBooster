void printFirst ( UBreakIterator * boundary , UChar * str ) {
 int32_t end ;
 int32_t start = ubrk_first ( boundary ) ;
 end = ubrk_next ( boundary ) ;
 printTextRange ( str , start , end ) ;
 }