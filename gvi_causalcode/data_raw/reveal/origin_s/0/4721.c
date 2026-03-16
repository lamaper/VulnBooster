static UBool U_CALLCONV lenient8IteratorHasNext ( UCharIterator * iter ) {
 return iter -> reservedField != 0 || iter -> start < iter -> limit ;
 }