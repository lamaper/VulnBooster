static void update_skip_probs ( VP9_COMMON * cm , vp9_writer * w ) {
 int k ;
 for ( k = 0 ;
 k < SKIP_CONTEXTS ;
 ++ k ) vp9_cond_prob_diff_update ( w , & cm -> fc . skip_probs [ k ] , cm -> counts . skip [ k ] ) ;
 }