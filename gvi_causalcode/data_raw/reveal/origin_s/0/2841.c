int vp9_full_pixel_diamond ( const VP9_COMP * cpi , MACROBLOCK * x , MV * mvp_full , int step_param , int sadpb , int further_steps , int do_refine , const vp9_variance_fn_ptr_t * fn_ptr , const MV * ref_mv , MV * dst_mv ) {
 MV temp_mv ;
 int thissme , n , num00 = 0 ;
 int bestsme = cpi -> diamond_search_sad ( x , & cpi -> ss_cfg , mvp_full , & temp_mv , step_param , sadpb , & n , fn_ptr , ref_mv ) ;
 if ( bestsme < INT_MAX ) bestsme = vp9_get_mvpred_var ( x , & temp_mv , ref_mv , fn_ptr , 1 ) ;
 * dst_mv = temp_mv ;
 if ( n > further_steps ) do_refine = 0 ;
 while ( n < further_steps ) {
 ++ n ;
 if ( num00 ) {
 num00 -- ;
 }
 else {
 thissme = cpi -> diamond_search_sad ( x , & cpi -> ss_cfg , mvp_full , & temp_mv , step_param + n , sadpb , & num00 , fn_ptr , ref_mv ) ;
 if ( thissme < INT_MAX ) thissme = vp9_get_mvpred_var ( x , & temp_mv , ref_mv , fn_ptr , 1 ) ;
 if ( num00 > further_steps - n ) do_refine = 0 ;
 if ( thissme < bestsme ) {
 bestsme = thissme ;
 * dst_mv = temp_mv ;
 }
 }
 }
 if ( do_refine ) {
 const int search_range = 8 ;
 MV best_mv = * dst_mv ;
 thissme = cpi -> refining_search_sad ( x , & best_mv , sadpb , search_range , fn_ptr , ref_mv ) ;
 if ( thissme < INT_MAX ) thissme = vp9_get_mvpred_var ( x , & best_mv , ref_mv , fn_ptr , 1 ) ;
 if ( thissme < bestsme ) {
 bestsme = thissme ;
 * dst_mv = best_mv ;
 }
 }
 return bestsme ;
 }