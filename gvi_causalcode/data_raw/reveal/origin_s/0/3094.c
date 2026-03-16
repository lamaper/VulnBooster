int vp9_find_best_sub_pixel_tree ( const MACROBLOCK * x , MV * bestmv , const MV * ref_mv , int allow_hp , int error_per_bit , const vp9_variance_fn_ptr_t * vfp , int forced_stop , int iters_per_step , int * sad_list , int * mvjcost , int * mvcost [ 2 ] , int * distortion , unsigned int * sse1 , const uint8_t * second_pred , int w , int h ) {
 SETUP_SUBPEL_SEARCH ;
 ( void ) sad_list ;
 FIRST_LEVEL_CHECKS ;
 if ( halfiters > 1 ) {
 SECOND_LEVEL_CHECKS ;
 }
 tr = br ;
 tc = bc ;
 if ( forced_stop != 2 ) {
 hstep >>= 1 ;
 FIRST_LEVEL_CHECKS ;
 if ( quarteriters > 1 ) {
 SECOND_LEVEL_CHECKS ;
 }
 tr = br ;
 tc = bc ;
 }
 if ( allow_hp && vp9_use_mv_hp ( ref_mv ) && forced_stop == 0 ) {
 hstep >>= 1 ;
 FIRST_LEVEL_CHECKS ;
 if ( eighthiters > 1 ) {
 SECOND_LEVEL_CHECKS ;
 }
 tr = br ;
 tc = bc ;
 }
 ( void ) tr ;
 ( void ) tc ;
 bestmv -> row = br ;
 bestmv -> col = bc ;
 if ( ( abs ( bestmv -> col - ref_mv -> col ) > ( MAX_FULL_PEL_VAL << 3 ) ) || ( abs ( bestmv -> row - ref_mv -> row ) > ( MAX_FULL_PEL_VAL << 3 ) ) ) return INT_MAX ;
 return besterr ;
 }