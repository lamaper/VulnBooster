int xmlCharInRange ( unsigned int val , const xmlChRangeGroup * rptr ) {
 int low , high , mid ;
 const xmlChSRange * sptr ;
 const xmlChLRange * lptr ;
 if ( rptr == NULL ) return ( 0 ) ;
 if ( val < 0x10000 ) {
 if ( rptr -> nbShortRange == 0 ) return 0 ;
 low = 0 ;
 high = rptr -> nbShortRange - 1 ;
 sptr = rptr -> shortRange ;
 while ( low <= high ) {
 mid = ( low + high ) / 2 ;
 if ( ( unsigned short ) val < sptr [ mid ] . low ) {
 high = mid - 1 ;
 }
 else {
 if ( ( unsigned short ) val > sptr [ mid ] . high ) {
 low = mid + 1 ;
 }
 else {
 return 1 ;
 }
 }
 }
 }
 else {
 if ( rptr -> nbLongRange == 0 ) {
 return 0 ;
 }
 low = 0 ;
 high = rptr -> nbLongRange - 1 ;
 lptr = rptr -> longRange ;
 while ( low <= high ) {
 mid = ( low + high ) / 2 ;
 if ( val < lptr [ mid ] . low ) {
 high = mid - 1 ;
 }
 else {
 if ( val > lptr [ mid ] . high ) {
 low = mid + 1 ;
 }
 else {
 return 1 ;
 }
 }
 }
 }
 return 0 ;
 }