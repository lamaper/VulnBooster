void vp9_initialize_enc ( ) {
 static int init_done = 0 ;
 if ( ! init_done ) {
 vp9_rtcd ( ) ;
 vp9_init_neighbors ( ) ;
 vp9_init_intra_predictors ( ) ;
 vp9_coef_tree_initialize ( ) ;
 vp9_tokenize_initialize ( ) ;
 vp9_init_me_luts ( ) ;
 vp9_rc_init_minq_luts ( ) ;
 vp9_entropy_mv_init ( ) ;
 vp9_entropy_mode_init ( ) ;
 vp9_temporal_filter_init ( ) ;
 init_done = 1 ;
 }
 }