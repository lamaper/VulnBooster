static void initialize_dec ( ) {
 static int init_done = 0 ;
 if ( ! init_done ) {
 vp9_rtcd ( ) ;
 vp9_init_neighbors ( ) ;
 vp9_init_intra_predictors ( ) ;
 init_done = 1 ;
 }
 }