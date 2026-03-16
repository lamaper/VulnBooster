static void update_rd_thresh_fact ( VP9_COMP * cpi , int bsize , int best_mode_index ) {
 if ( cpi -> sf . adaptive_rd_thresh > 0 ) {
 const int top_mode = bsize < BLOCK_8X8 ? MAX_REFS : MAX_MODES ;
 int mode ;
 for ( mode = 0 ;
 mode < top_mode ;
 ++ mode ) {
 int * const fact = & cpi -> rd . thresh_freq_fact [ bsize ] [ mode ] ;
 if ( mode == best_mode_index ) {
 * fact -= ( * fact >> 3 ) ;
 }
 else {
 * fact = MIN ( * fact + RD_THRESH_INC , cpi -> sf . adaptive_rd_thresh * RD_THRESH_MAX_FACT ) ;
 }
 }
 }
 }