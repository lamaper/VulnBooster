static int vp9_pattern_search ( const MACROBLOCK * x , MV * ref_mv , int search_param , int sad_per_bit , int do_init_search , int * sad_list , const vp9_variance_fn_ptr_t * vfp , int use_mvcost , const MV * center_mv , MV * best_mv , const int num_candidates [ MAX_PATTERN_SCALES ] , const MV candidates [ MAX_PATTERN_SCALES ] [ MAX_PATTERN_CANDIDATES ] ) {
 const MACROBLOCKD * const xd = & x -> e_mbd ;
 static const int search_param_to_steps [ MAX_MVSEARCH_STEPS ] = {
 10 , 9 , 8 , 7 , 6 , 5 , 4 , 3 , 2 , 1 , 0 , }
 ;
 int i , s , t ;
 const struct buf_2d * const what = & x -> plane [ 0 ] . src ;
 const struct buf_2d * const in_what = & xd -> plane [ 0 ] . pre [ 0 ] ;
 int br , bc ;
 int bestsad = INT_MAX ;
 int thissad ;
 int k = - 1 ;
 const MV fcenter_mv = {
 center_mv -> row >> 3 , center_mv -> col >> 3 }
 ;
 int best_init_s = search_param_to_steps [ search_param ] ;
 clamp_mv ( ref_mv , x -> mv_col_min , x -> mv_col_max , x -> mv_row_min , x -> mv_row_max ) ;
 br = ref_mv -> row ;
 bc = ref_mv -> col ;
 bestsad = vfp -> sdf ( what -> buf , what -> stride , get_buf_from_mv ( in_what , ref_mv ) , in_what -> stride ) + mvsad_err_cost ( x , ref_mv , & fcenter_mv , sad_per_bit ) ;
 if ( do_init_search ) {
 s = best_init_s ;
 best_init_s = - 1 ;
 for ( t = 0 ;
 t <= s ;
 ++ t ) {
 int best_site = - 1 ;
 if ( check_bounds ( x , br , bc , 1 << t ) ) {
 for ( i = 0 ;
 i < num_candidates [ t ] ;
 i ++ ) {
 const MV this_mv = {
 br + candidates [ t ] [ i ] . row , bc + candidates [ t ] [ i ] . col }
 ;
 thissad = vfp -> sdf ( what -> buf , what -> stride , get_buf_from_mv ( in_what , & this_mv ) , in_what -> stride ) ;
 CHECK_BETTER }
 }
 else {
 for ( i = 0 ;
 i < num_candidates [ t ] ;
 i ++ ) {
 const MV this_mv = {
 br + candidates [ t ] [ i ] . row , bc + candidates [ t ] [ i ] . col }
 ;
 if ( ! is_mv_in ( x , & this_mv ) ) continue ;
 thissad = vfp -> sdf ( what -> buf , what -> stride , get_buf_from_mv ( in_what , & this_mv ) , in_what -> stride ) ;
 CHECK_BETTER }
 }
 if ( best_site == - 1 ) {
 continue ;
 }
 else {
 best_init_s = t ;
 k = best_site ;
 }
 }
 if ( best_init_s != - 1 ) {
 br += candidates [ best_init_s ] [ k ] . row ;
 bc += candidates [ best_init_s ] [ k ] . col ;
 }
 }
 if ( best_init_s != - 1 ) {
 int best_site = - 1 ;
 s = best_init_s ;
 do {
 if ( ! do_init_search || s != best_init_s ) {
 if ( check_bounds ( x , br , bc , 1 << s ) ) {
 for ( i = 0 ;
 i < num_candidates [ s ] ;
 i ++ ) {
 const MV this_mv = {
 br + candidates [ s ] [ i ] . row , bc + candidates [ s ] [ i ] . col }
 ;
 thissad = vfp -> sdf ( what -> buf , what -> stride , get_buf_from_mv ( in_what , & this_mv ) , in_what -> stride ) ;
 CHECK_BETTER }
 }
 else {
 for ( i = 0 ;
 i < num_candidates [ s ] ;
 i ++ ) {
 const MV this_mv = {
 br + candidates [ s ] [ i ] . row , bc + candidates [ s ] [ i ] . col }
 ;
 if ( ! is_mv_in ( x , & this_mv ) ) continue ;
 thissad = vfp -> sdf ( what -> buf , what -> stride , get_buf_from_mv ( in_what , & this_mv ) , in_what -> stride ) ;
 CHECK_BETTER }
 }
 if ( best_site == - 1 ) {
 continue ;
 }
 else {
 br += candidates [ s ] [ best_site ] . row ;
 bc += candidates [ s ] [ best_site ] . col ;
 k = best_site ;
 }
 }
 do {
 int next_chkpts_indices [ PATTERN_CANDIDATES_REF ] ;
 best_site = - 1 ;
 next_chkpts_indices [ 0 ] = ( k == 0 ) ? num_candidates [ s ] - 1 : k - 1 ;
 next_chkpts_indices [ 1 ] = k ;
 next_chkpts_indices [ 2 ] = ( k == num_candidates [ s ] - 1 ) ? 0 : k + 1 ;
 if ( check_bounds ( x , br , bc , 1 << s ) ) {
 for ( i = 0 ;
 i < PATTERN_CANDIDATES_REF ;
 i ++ ) {
 const MV this_mv = {
 br + candidates [ s ] [ next_chkpts_indices [ i ] ] . row , bc + candidates [ s ] [ next_chkpts_indices [ i ] ] . col }
 ;
 thissad = vfp -> sdf ( what -> buf , what -> stride , get_buf_from_mv ( in_what , & this_mv ) , in_what -> stride ) ;
 CHECK_BETTER }
 }
 else {
 for ( i = 0 ;
 i < PATTERN_CANDIDATES_REF ;
 i ++ ) {
 const MV this_mv = {
 br + candidates [ s ] [ next_chkpts_indices [ i ] ] . row , bc + candidates [ s ] [ next_chkpts_indices [ i ] ] . col }
 ;
 if ( ! is_mv_in ( x , & this_mv ) ) continue ;
 thissad = vfp -> sdf ( what -> buf , what -> stride , get_buf_from_mv ( in_what , & this_mv ) , in_what -> stride ) ;
 CHECK_BETTER }
 }
 if ( best_site != - 1 ) {
 k = next_chkpts_indices [ best_site ] ;
 br += candidates [ s ] [ k ] . row ;
 bc += candidates [ s ] [ k ] . col ;
 }
 }
 while ( best_site != - 1 ) ;
 }
 while ( s -- ) ;
 }
 if ( sad_list ) {
 static const MV neighbors [ 4 ] = {
 {
 0 , - 1 }
 , {
 - 1 , 0 }
 , {
 0 , 1 }
 , {
 1 , 0 }
 }
 ;
 sad_list [ 0 ] = bestsad ;
 if ( check_bounds ( x , br , bc , 1 ) ) {
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 const MV this_mv = {
 br + neighbors [ i ] . row , bc + neighbors [ i ] . col }
 ;
 sad_list [ i + 1 ] = vfp -> sdf ( what -> buf , what -> stride , get_buf_from_mv ( in_what , & this_mv ) , in_what -> stride ) ;
 }
 }
 else {
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 const MV this_mv = {
 br + neighbors [ i ] . row , bc + neighbors [ i ] . col }
 ;
 if ( ! is_mv_in ( x , & this_mv ) ) sad_list [ i + 1 ] = INT_MAX ;
 else sad_list [ i + 1 ] = vfp -> sdf ( what -> buf , what -> stride , get_buf_from_mv ( in_what , & this_mv ) , in_what -> stride ) ;
 }
 }
 }
 best_mv -> row = br ;
 best_mv -> col = bc ;
 return bestsad ;
 }