static int get_active_quality ( int q , int gfu_boost , int low , int high , int * low_motion_minq , int * high_motion_minq ) {
 if ( gfu_boost > high ) {
 return low_motion_minq [ q ] ;
 }
 else if ( gfu_boost < low ) {
 return high_motion_minq [ q ] ;
 }
 else {
 const int gap = high - low ;
 const int offset = high - gfu_boost ;
 const int qdiff = high_motion_minq [ q ] - low_motion_minq [ q ] ;
 const int adjustment = ( ( offset * qdiff ) + ( gap >> 1 ) ) / gap ;
 return low_motion_minq [ q ] + adjustment ;
 }
 }