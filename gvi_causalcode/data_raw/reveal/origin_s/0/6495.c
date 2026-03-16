static void _updateOffsets ( int32_t * offsets , int32_t length , int32_t sourceIndex , int32_t errorInputLength ) {
 int32_t * limit ;
 int32_t delta , offset ;
 if ( sourceIndex >= 0 ) {
 delta = sourceIndex - errorInputLength ;
 }
 else {
 delta = - 1 ;
 }
 limit = offsets + length ;
 if ( delta == 0 ) {
 }
 else if ( delta > 0 ) {
 while ( offsets < limit ) {
 offset = * offsets ;
 if ( offset >= 0 ) {
 * offsets = offset + delta ;
 }
 ++ offsets ;
 }
 }
 else {
 while ( offsets < limit ) {
 * offsets ++ = - 1 ;
 }
 }
 }