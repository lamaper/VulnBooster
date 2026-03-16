static void compareIterators ( UCharIterator * iter1 , const char * n1 , UCharIterator * iter2 , const char * n2 ) {
 int32_t i , pos1 , pos2 , middle , length ;
 UChar32 c1 , c2 ;
 length = iter1 -> getIndex ( iter1 , UITER_LENGTH ) ;
 pos2 = iter2 -> getIndex ( iter2 , UITER_LENGTH ) ;
 if ( length != pos2 ) {
 log_err ( "%s->getIndex(length)=%d != %d=%s->getIndex(length)\n" , n1 , length , pos2 , n2 ) ;
 return ;
 }
 middle = length / 2 ;
 pos1 = iter1 -> move ( iter1 , middle , UITER_ZERO ) ;
 if ( pos1 != middle ) {
 log_err ( "%s->move(from 0 to middle %d)=%d does not move to the middle\n" , n1 , middle , pos1 ) ;
 return ;
 }
 pos2 = iter2 -> move ( iter2 , middle , UITER_ZERO ) ;
 if ( pos2 != middle ) {
 log_err ( "%s->move(from 0 to middle %d)=%d does not move to the middle\n" , n2 , middle , pos2 ) ;
 return ;
 }
 c1 = iter1 -> current ( iter1 ) ;
 c2 = iter2 -> current ( iter2 ) ;
 if ( c1 != c2 ) {
 log_err ( "%s->current()=U+%04x != U+%04x=%s->current() at middle=%d\n" , n1 , c1 , c2 , n2 , middle ) ;
 return ;
 }
 for ( i = 0 ;
 i < 3 ;
 ++ i ) {
 c1 = iter1 -> next ( iter1 ) ;
 c2 = iter2 -> next ( iter2 ) ;
 if ( c1 != c2 ) {
 log_err ( "%s->next()=U+%04x != U+%04x=%s->next() at %d (started in middle)\n" , n1 , c1 , c2 , n2 , iter1 -> getIndex ( iter1 , UITER_CURRENT ) ) ;
 return ;
 }
 }
 for ( i = 0 ;
 i < 5 ;
 ++ i ) {
 c1 = iter1 -> previous ( iter1 ) ;
 c2 = iter2 -> previous ( iter2 ) ;
 if ( c1 != c2 ) {
 log_err ( "%s->previous()=U+%04x != U+%04x=%s->previous() at %d (started in middle)\n" , n1 , c1 , c2 , n2 , iter1 -> getIndex ( iter1 , UITER_CURRENT ) ) ;
 return ;
 }
 }
 pos1 = iter1 -> move ( iter1 , 0 , UITER_START ) ;
 if ( pos1 < 0 ) {
 log_err ( "%s->move(start) failed\n" , n1 ) ;
 return ;
 }
 if ( ! iter1 -> hasNext ( iter1 ) ) {
 log_err ( "%s->hasNext() at the start returns FALSE\n" , n1 ) ;
 return ;
 }
 pos2 = iter2 -> move ( iter2 , 0 , UITER_START ) ;
 if ( pos2 < 0 ) {
 log_err ( "%s->move(start) failed\n" , n2 ) ;
 return ;
 }
 if ( ! iter2 -> hasNext ( iter2 ) ) {
 log_err ( "%s->hasNext() at the start returns FALSE\n" , n2 ) ;
 return ;
 }
 do {
 c1 = iter1 -> next ( iter1 ) ;
 c2 = iter2 -> next ( iter2 ) ;
 if ( c1 != c2 ) {
 log_err ( "%s->next()=U+%04x != U+%04x=%s->next() at %d\n" , n1 , c1 , c2 , n2 , iter1 -> getIndex ( iter1 , UITER_CURRENT ) ) ;
 return ;
 }
 }
 while ( c1 >= 0 ) ;
 if ( iter1 -> hasNext ( iter1 ) ) {
 log_err ( "%s->hasNext() at the end returns TRUE\n" , n1 ) ;
 return ;
 }
 if ( iter2 -> hasNext ( iter2 ) ) {
 log_err ( "%s->hasNext() at the end returns TRUE\n" , n2 ) ;
 return ;
 }
 pos1 = iter1 -> move ( iter1 , middle , UITER_ZERO ) ;
 if ( pos1 != middle ) {
 log_err ( "%s->move(from end to middle %d)=%d does not move to the middle\n" , n1 , middle , pos1 ) ;
 return ;
 }
 pos2 = iter2 -> move ( iter2 , middle , UITER_ZERO ) ;
 if ( pos2 != middle ) {
 log_err ( "%s->move(from end to middle %d)=%d does not move to the middle\n" , n2 , middle , pos2 ) ;
 return ;
 }
 pos1 = iter1 -> move ( iter1 , 1 , UITER_ZERO ) ;
 if ( pos1 != 1 ) {
 log_err ( "%s->move(from middle %d to 1)=%d does not move to 1\n" , n1 , middle , pos1 ) ;
 return ;
 }
 pos2 = iter2 -> move ( iter2 , 1 , UITER_ZERO ) ;
 if ( pos2 != 1 ) {
 log_err ( "%s->move(from middle %d to 1)=%d does not move to 1\n" , n2 , middle , pos2 ) ;
 return ;
 }
 pos1 = iter1 -> move ( iter1 , 0 , UITER_LIMIT ) ;
 if ( pos1 < 0 ) {
 log_err ( "%s->move(limit) failed\n" , n1 ) ;
 return ;
 }
 if ( ! iter1 -> hasPrevious ( iter1 ) ) {
 log_err ( "%s->hasPrevious() at the end returns FALSE\n" , n1 ) ;
 return ;
 }
 pos2 = iter2 -> move ( iter2 , 0 , UITER_LIMIT ) ;
 if ( pos2 < 0 ) {
 log_err ( "%s->move(limit) failed\n" , n2 ) ;
 return ;
 }
 if ( ! iter2 -> hasPrevious ( iter2 ) ) {
 log_err ( "%s->hasPrevious() at the end returns FALSE\n" , n2 ) ;
 return ;
 }
 do {
 c1 = iter1 -> previous ( iter1 ) ;
 c2 = iter2 -> previous ( iter2 ) ;
 if ( c1 != c2 ) {
 log_err ( "%s->previous()=U+%04x != U+%04x=%s->previous() at %d\n" , n1 , c1 , c2 , n2 , iter1 -> getIndex ( iter1 , UITER_CURRENT ) ) ;
 return ;
 }
 }
 while ( c1 >= 0 ) ;
 if ( iter1 -> hasPrevious ( iter1 ) ) {
 log_err ( "%s->hasPrevious() at the start returns TRUE\n" , n1 ) ;
 return ;
 }
 if ( iter2 -> hasPrevious ( iter2 ) ) {
 log_err ( "%s->hasPrevious() at the start returns TRUE\n" , n2 ) ;
 return ;
 }
 }