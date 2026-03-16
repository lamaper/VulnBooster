static void debug_check_frame_counts ( const VP9_COMMON * const cm ) {
 FRAME_COUNTS zero_counts ;
 vp9_zero ( zero_counts ) ;
 assert ( cm -> frame_parallel_decoding_mode || cm -> error_resilient_mode ) ;
 assert ( ! memcmp ( cm -> counts . y_mode , zero_counts . y_mode , sizeof ( cm -> counts . y_mode ) ) ) ;
 assert ( ! memcmp ( cm -> counts . uv_mode , zero_counts . uv_mode , sizeof ( cm -> counts . uv_mode ) ) ) ;
 assert ( ! memcmp ( cm -> counts . partition , zero_counts . partition , sizeof ( cm -> counts . partition ) ) ) ;
 assert ( ! memcmp ( cm -> counts . coef , zero_counts . coef , sizeof ( cm -> counts . coef ) ) ) ;
 assert ( ! memcmp ( cm -> counts . eob_branch , zero_counts . eob_branch , sizeof ( cm -> counts . eob_branch ) ) ) ;
 assert ( ! memcmp ( cm -> counts . switchable_interp , zero_counts . switchable_interp , sizeof ( cm -> counts . switchable_interp ) ) ) ;
 assert ( ! memcmp ( cm -> counts . inter_mode , zero_counts . inter_mode , sizeof ( cm -> counts . inter_mode ) ) ) ;
 assert ( ! memcmp ( cm -> counts . intra_inter , zero_counts . intra_inter , sizeof ( cm -> counts . intra_inter ) ) ) ;
 assert ( ! memcmp ( cm -> counts . comp_inter , zero_counts . comp_inter , sizeof ( cm -> counts . comp_inter ) ) ) ;
 assert ( ! memcmp ( cm -> counts . single_ref , zero_counts . single_ref , sizeof ( cm -> counts . single_ref ) ) ) ;
 assert ( ! memcmp ( cm -> counts . comp_ref , zero_counts . comp_ref , sizeof ( cm -> counts . comp_ref ) ) ) ;
 assert ( ! memcmp ( & cm -> counts . tx , & zero_counts . tx , sizeof ( cm -> counts . tx ) ) ) ;
 assert ( ! memcmp ( cm -> counts . skip , zero_counts . skip , sizeof ( cm -> counts . skip ) ) ) ;
 assert ( ! memcmp ( & cm -> counts . mv , & zero_counts . mv , sizeof ( cm -> counts . mv ) ) ) ;
 }