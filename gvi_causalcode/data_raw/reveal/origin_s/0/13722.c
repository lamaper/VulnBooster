static SplinePointList * EraseStroke ( SplineChar * sc , SplinePointList * head , SplinePointList * erase ) {
 SplineSet * spl , * last ;
 SplinePoint * sp ;
 if ( head == NULL ) {
 SplinePointListsFree ( erase ) ;
 return ( NULL ) ;
 }
 last = NULL ;
 for ( spl = head ;
 spl != NULL ;
 spl = spl -> next ) {
 for ( sp = spl -> first ;
 sp != NULL ;
 ) {
 sp -> selected = false ;
 if ( sp -> next == NULL ) break ;
 sp = sp -> next -> to ;
 if ( sp == spl -> first ) break ;
 }
 last = spl ;
 }
 for ( spl = erase ;
 spl != NULL ;
 spl = spl -> next ) {
 for ( sp = spl -> first ;
 sp != NULL ;
 ) {
 sp -> selected = true ;
 if ( sp -> next == NULL ) break ;
 sp = sp -> next -> to ;
 if ( sp == spl -> first ) break ;
 }
 }
 last -> next = erase ;
 return ( SplineSetRemoveOverlap ( sc , head , over_exclude ) ) ;
 }