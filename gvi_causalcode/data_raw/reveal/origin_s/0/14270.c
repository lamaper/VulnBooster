static void testIteratorState ( UCharIterator * iter1 , UCharIterator * iter2 , const char * n , int32_t middle ) {
 UChar32 u [ 4 ] ;
 UErrorCode errorCode ;
 UChar32 c ;
 uint32_t state ;
 int32_t i , j ;
 iter1 -> move ( iter1 , middle - 2 , UITER_ZERO ) ;
 for ( i = 0 ;
 i < 4 ;
 ++ i ) {
 c = iter1 -> next ( iter1 ) ;
 if ( c < 0 ) {
 log_err ( "test error: %s[%d]=%d\n" , n , middle - 2 + i , c ) ;
 return ;
 }
 u [ i ] = c ;
 }
 iter1 -> move ( iter1 , - 2 , UITER_CURRENT ) ;
 state = uiter_getState ( iter1 ) ;
 errorCode = U_ZERO_ERROR ;
 uiter_setState ( iter2 , state , & errorCode ) ;
 if ( U_FAILURE ( errorCode ) ) {
 log_err ( "%s->setState(0x%x) failed: %s\n" , n , state , u_errorName ( errorCode ) ) ;
 return ;
 }
 c = iter2 -> current ( iter2 ) ;
 if ( c != u [ 2 ] ) {
 log_err ( "%s->current(at %d)=U+%04x!=U+%04x\n" , n , middle , c , u [ 2 ] ) ;
 }
 c = iter2 -> previous ( iter2 ) ;
 if ( c != u [ 1 ] ) {
 log_err ( "%s->previous(at %d)=U+%04x!=U+%04x\n" , n , middle - 1 , c , u [ 1 ] ) ;
 }
 iter2 -> move ( iter2 , 2 , UITER_CURRENT ) ;
 c = iter2 -> next ( iter2 ) ;
 if ( c != u [ 3 ] ) {
 log_err ( "%s->next(at %d)=U+%04x!=U+%04x\n" , n , middle + 1 , c , u [ 3 ] ) ;
 }
 iter2 -> move ( iter2 , - 3 , UITER_CURRENT ) ;
 c = iter2 -> previous ( iter2 ) ;
 if ( c != u [ 0 ] ) {
 log_err ( "%s->previous(at %d)=U+%04x!=U+%04x\n" , n , middle - 2 , c , u [ 0 ] ) ;
 }
 iter2 -> move ( iter2 , 1 , UITER_CURRENT ) ;
 iter2 -> next ( iter2 ) ;
 i = iter1 -> getIndex ( iter1 , UITER_CURRENT ) ;
 j = iter2 -> getIndex ( iter2 , UITER_CURRENT ) ;
 if ( i != middle ) {
 log_err ( "%s->getIndex(current)=%d!=%d as expected\n" , n , i , middle ) ;
 }
 if ( i != j ) {
 log_err ( "%s->getIndex(current)=%d!=%d after setState()\n" , n , j , i ) ;
 }
 i = iter1 -> getIndex ( iter1 , UITER_LENGTH ) ;
 j = iter2 -> getIndex ( iter2 , UITER_LENGTH ) ;
 if ( i != j ) {
 log_err ( "%s->getIndex(length)=%d!=%d before/after setState()\n" , n , i , j ) ;
 }
 }