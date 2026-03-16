int vp9_full_pixel_search ( VP9_COMP * cpi , MACROBLOCK * x , BLOCK_SIZE bsize , MV * mvp_full , int step_param , int error_per_bit , int * sad_list , const MV * ref_mv , MV * tmp_mv , int var_max , int rd ) {
 const SPEED_FEATURES * const sf = & cpi -> sf ;
 const SEARCH_METHODS method = sf -> mv . search_method ;
 vp9_variance_fn_ptr_t * fn_ptr = & cpi -> fn_ptr [ bsize ] ;
 int var = 0 ;
 if ( sad_list ) {
 sad_list [ 0 ] = INT_MAX ;
 sad_list [ 1 ] = INT_MAX ;
 sad_list [ 2 ] = INT_MAX ;
 sad_list [ 3 ] = INT_MAX ;
 sad_list [ 4 ] = INT_MAX ;
 }
 switch ( method ) {
 case FAST_DIAMOND : var = vp9_fast_dia_search ( x , mvp_full , step_param , error_per_bit , 0 , sad_list , fn_ptr , 1 , ref_mv , tmp_mv ) ;
 break ;
 case FAST_HEX : var = vp9_fast_hex_search ( x , mvp_full , step_param , error_per_bit , 0 , sad_list , fn_ptr , 1 , ref_mv , tmp_mv ) ;
 break ;
 case HEX : var = vp9_hex_search ( x , mvp_full , step_param , error_per_bit , 1 , sad_list , fn_ptr , 1 , ref_mv , tmp_mv ) ;
 break ;
 case SQUARE : var = vp9_square_search ( x , mvp_full , step_param , error_per_bit , 1 , sad_list , fn_ptr , 1 , ref_mv , tmp_mv ) ;
 break ;
 case BIGDIA : var = vp9_bigdia_search ( x , mvp_full , step_param , error_per_bit , 1 , sad_list , fn_ptr , 1 , ref_mv , tmp_mv ) ;
 break ;
 case NSTEP : var = vp9_full_pixel_diamond ( cpi , x , mvp_full , step_param , error_per_bit , MAX_MVSEARCH_STEPS - 1 - step_param , 1 , fn_ptr , ref_mv , tmp_mv ) ;
 break ;
 default : assert ( ! "Invalid search method." ) ;
 }
 if ( method != NSTEP && rd && var < var_max ) var = vp9_get_mvpred_var ( x , tmp_mv , ref_mv , fn_ptr , 1 ) ;
 return var ;
 }