static void subQuickSort ( char * array , int32_t start , int32_t limit , int32_t itemSize , UComparator * cmp , const void * context , void * px , void * pw ) {
 int32_t left , right ;
 do {
 if ( ( start + MIN_QSORT ) >= limit ) {
 doInsertionSort ( array + start * itemSize , limit - start , itemSize , cmp , context , px ) ;
 break ;
 }
 left = start ;
 right = limit ;
 uprv_memcpy ( px , array + ( size_t ) ( ( start + limit ) / 2 ) * itemSize , itemSize ) ;
 do {
 while ( cmp ( context , array + left * itemSize , px ) < 0 ) {
 ++ left ;
 }
 while ( cmp ( context , px , array + ( right - 1 ) * itemSize ) < 0 ) {
 -- right ;
 }
 if ( left < right ) {
 -- right ;
 if ( left < right ) {
 uprv_memcpy ( pw , array + ( size_t ) left * itemSize , itemSize ) ;
 uprv_memcpy ( array + ( size_t ) left * itemSize , array + ( size_t ) right * itemSize , itemSize ) ;
 uprv_memcpy ( array + ( size_t ) right * itemSize , pw , itemSize ) ;
 }
 ++ left ;
 }
 }
 while ( left < right ) ;
 if ( ( right - start ) < ( limit - left ) ) {
 if ( start < ( right - 1 ) ) {
 subQuickSort ( array , start , right , itemSize , cmp , context , px , pw ) ;
 }
 start = left ;
 }
 else {
 if ( left < ( limit - 1 ) ) {
 subQuickSort ( array , left , limit , itemSize , cmp , context , px , pw ) ;
 }
 limit = right ;
 }
 }
 while ( start < ( limit - 1 ) ) ;
 }