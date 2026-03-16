static void update_switchable_interp_probs ( VP9_COMMON * cm , vp9_writer * w ) {
 int j ;
 for ( j = 0 ;
 j < SWITCHABLE_FILTER_CONTEXTS ;
 ++ j ) prob_diff_update ( vp9_switchable_interp_tree , cm -> fc . switchable_interp_prob [ j ] , cm -> counts . switchable_interp [ j ] , SWITCHABLE_FILTERS , w ) ;
 }