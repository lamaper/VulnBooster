static const FIRSTPASS_STATS * read_frame_stats ( const TWO_PASS * p , int offset ) {
 if ( ( offset >= 0 && p -> stats_in + offset >= p -> stats_in_end ) || ( offset < 0 && p -> stats_in + offset < p -> stats_in_start ) ) {
 return NULL ;
 }
 return & p -> stats_in [ offset ] ;
 }