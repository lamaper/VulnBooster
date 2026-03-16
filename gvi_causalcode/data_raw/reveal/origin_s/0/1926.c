static void rv40_adaptive_loop_filter ( RV34DSPContext * rdsp , uint8_t * src , int stride , int dmode , int lim_q1 , int lim_p1 , int alpha , int beta , int beta2 , int chroma , int edge , int dir ) {
 int filter_p1 , filter_q1 ;
 int strong ;
 int lims ;
 strong = rdsp -> rv40_loop_filter_strength [ dir ] ( src , stride , beta , beta2 , edge , & filter_p1 , & filter_q1 ) ;
 lims = filter_p1 + filter_q1 + ( ( lim_q1 + lim_p1 ) >> 1 ) + 1 ;
 if ( strong ) {
 rdsp -> rv40_strong_loop_filter [ dir ] ( src , stride , alpha , lims , dmode , chroma ) ;
 }
 else if ( filter_p1 & filter_q1 ) {
 rdsp -> rv40_weak_loop_filter [ dir ] ( src , stride , 1 , 1 , alpha , beta , lims , lim_q1 , lim_p1 ) ;
 }
 else if ( filter_p1 | filter_q1 ) {
 rdsp -> rv40_weak_loop_filter [ dir ] ( src , stride , filter_p1 , filter_q1 , alpha , beta , lims >> 1 , lim_q1 >> 1 , lim_p1 >> 1 ) ;
 }
 }