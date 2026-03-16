void vp9_find_best_ref_mvs ( MACROBLOCKD * xd , int allow_hp , int_mv * mvlist , int_mv * nearest , int_mv * near ) {
 int i ;
 for ( i = 0 ;
 i < MAX_MV_REF_CANDIDATES ;
 ++ i ) {
 lower_mv_precision ( & mvlist [ i ] . as_mv , allow_hp ) ;
 clamp_mv2 ( & mvlist [ i ] . as_mv , xd ) ;
 }
 * nearest = mvlist [ 0 ] ;
 * near = mvlist [ 1 ] ;
 }