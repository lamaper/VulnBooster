static SplineSet * SCttfApprox ( SplineChar * sc , int layer ) {
 SplineSet * head = NULL , * last , * ss , * tss ;
 RefChar * ref ;
 for ( ss = sc -> layers [ layer ] . splines ;
 ss != NULL ;
 ss = ss -> next ) {
 tss = sc -> layers [ layer ] . order2 ? SplinePointListCopy1 ( ss ) : SSttfApprox ( ss ) ;
 if ( head == NULL ) head = tss ;
 else last -> next = tss ;
 last = tss ;
 }
 for ( ref = sc -> layers [ layer ] . refs ;
 ref != NULL ;
 ref = ref -> next ) {
 for ( ss = ref -> layers [ 0 ] . splines ;
 ss != NULL ;
 ss = ss -> next ) {
 tss = sc -> layers [ layer ] . order2 ? SplinePointListCopy1 ( ss ) : SSttfApprox ( ss ) ;
 if ( head == NULL ) head = tss ;
 else last -> next = tss ;
 last = tss ;
 }
 }
 return ( head ) ;
 }