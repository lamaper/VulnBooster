static uint32_t * _findRow ( UPropsVectors * pv , UChar32 rangeStart ) {
 uint32_t * row ;
 int32_t columns , i , start , limit , prevRow ;
 columns = pv -> columns ;
 limit = pv -> rows ;
 prevRow = pv -> prevRow ;
 row = pv -> v + prevRow * columns ;
 if ( rangeStart >= ( UChar32 ) row [ 0 ] ) {
 if ( rangeStart < ( UChar32 ) row [ 1 ] ) {
 return row ;
 }
 else if ( rangeStart < ( UChar32 ) ( row += columns ) [ 1 ] ) {
 pv -> prevRow = prevRow + 1 ;
 return row ;
 }
 else if ( rangeStart < ( UChar32 ) ( row += columns ) [ 1 ] ) {
 pv -> prevRow = prevRow + 2 ;
 return row ;
 }
 else if ( ( rangeStart - ( UChar32 ) row [ 1 ] ) < 10 ) {
 prevRow += 2 ;
 do {
 ++ prevRow ;
 row += columns ;
 }
 while ( rangeStart >= ( UChar32 ) row [ 1 ] ) ;
 pv -> prevRow = prevRow ;
 return row ;
 }
 }
 else if ( rangeStart < ( UChar32 ) pv -> v [ 1 ] ) {
 pv -> prevRow = 0 ;
 return pv -> v ;
 }
 start = 0 ;
 while ( start < limit - 1 ) {
 i = ( start + limit ) / 2 ;
 row = pv -> v + i * columns ;
 if ( rangeStart < ( UChar32 ) row [ 0 ] ) {
 limit = i ;
 }
 else if ( rangeStart < ( UChar32 ) row [ 1 ] ) {
 pv -> prevRow = i ;
 return row ;
 }
 else {
 start = i ;
 }
 }
 pv -> prevRow = start ;
 return pv -> v + start * columns ;
 }