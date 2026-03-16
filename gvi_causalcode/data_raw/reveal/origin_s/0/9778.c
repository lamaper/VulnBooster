static void update_coef_probs_common ( vp9_writer * const bc , VP9_COMP * cpi , TX_SIZE tx_size , vp9_coeff_stats * frame_branch_ct , vp9_coeff_probs_model * new_coef_probs ) {
 vp9_coeff_probs_model * old_coef_probs = cpi -> common . fc . coef_probs [ tx_size ] ;
 const vp9_prob upd = DIFF_UPDATE_PROB ;
 const int entropy_nodes_update = UNCONSTRAINED_NODES ;
 int i , j , k , l , t ;
 switch ( cpi -> sf . use_fast_coef_updates ) {
 case TWO_LOOP : {
 int savings = 0 ;
 int update [ 2 ] = {
 0 , 0 }
 ;
 for ( i = 0 ;
 i < PLANE_TYPES ;
 ++ i ) {
 for ( j = 0 ;
 j < REF_TYPES ;
 ++ j ) {
 for ( k = 0 ;
 k < COEF_BANDS ;
 ++ k ) {
 for ( l = 0 ;
 l < BAND_COEFF_CONTEXTS ( k ) ;
 ++ l ) {
 for ( t = 0 ;
 t < entropy_nodes_update ;
 ++ t ) {
 vp9_prob newp = new_coef_probs [ i ] [ j ] [ k ] [ l ] [ t ] ;
 const vp9_prob oldp = old_coef_probs [ i ] [ j ] [ k ] [ l ] [ t ] ;
 int s ;
 int u = 0 ;
 if ( t == PIVOT_NODE ) s = vp9_prob_diff_update_savings_search_model ( frame_branch_ct [ i ] [ j ] [ k ] [ l ] [ 0 ] , old_coef_probs [ i ] [ j ] [ k ] [ l ] , & newp , upd ) ;
 else s = vp9_prob_diff_update_savings_search ( frame_branch_ct [ i ] [ j ] [ k ] [ l ] [ t ] , oldp , & newp , upd ) ;
 if ( s > 0 && newp != oldp ) u = 1 ;
 if ( u ) savings += s - ( int ) ( vp9_cost_zero ( upd ) ) ;
 else savings -= ( int ) ( vp9_cost_zero ( upd ) ) ;
 update [ u ] ++ ;
 }
 }
 }
 }
 }
 if ( update [ 1 ] == 0 || savings < 0 ) {
 vp9_write_bit ( bc , 0 ) ;
 return ;
 }
 vp9_write_bit ( bc , 1 ) ;
 for ( i = 0 ;
 i < PLANE_TYPES ;
 ++ i ) {
 for ( j = 0 ;
 j < REF_TYPES ;
 ++ j ) {
 for ( k = 0 ;
 k < COEF_BANDS ;
 ++ k ) {
 for ( l = 0 ;
 l < BAND_COEFF_CONTEXTS ( k ) ;
 ++ l ) {
 for ( t = 0 ;
 t < entropy_nodes_update ;
 ++ t ) {
 vp9_prob newp = new_coef_probs [ i ] [ j ] [ k ] [ l ] [ t ] ;
 vp9_prob * oldp = old_coef_probs [ i ] [ j ] [ k ] [ l ] + t ;
 const vp9_prob upd = DIFF_UPDATE_PROB ;
 int s ;
 int u = 0 ;
 if ( t == PIVOT_NODE ) s = vp9_prob_diff_update_savings_search_model ( frame_branch_ct [ i ] [ j ] [ k ] [ l ] [ 0 ] , old_coef_probs [ i ] [ j ] [ k ] [ l ] , & newp , upd ) ;
 else s = vp9_prob_diff_update_savings_search ( frame_branch_ct [ i ] [ j ] [ k ] [ l ] [ t ] , * oldp , & newp , upd ) ;
 if ( s > 0 && newp != * oldp ) u = 1 ;
 vp9_write ( bc , u , upd ) ;
 if ( u ) {
 vp9_write_prob_diff_update ( bc , newp , * oldp ) ;
 * oldp = newp ;
 }
 }
 }
 }
 }
 }
 return ;
 }
 case ONE_LOOP : case ONE_LOOP_REDUCED : {
 const int prev_coef_contexts_to_update = cpi -> sf . use_fast_coef_updates == ONE_LOOP_REDUCED ? COEFF_CONTEXTS >> 1 : COEFF_CONTEXTS ;
 const int coef_band_to_update = cpi -> sf . use_fast_coef_updates == ONE_LOOP_REDUCED ? COEF_BANDS >> 1 : COEF_BANDS ;
 int updates = 0 ;
 int noupdates_before_first = 0 ;
 for ( i = 0 ;
 i < PLANE_TYPES ;
 ++ i ) {
 for ( j = 0 ;
 j < REF_TYPES ;
 ++ j ) {
 for ( k = 0 ;
 k < COEF_BANDS ;
 ++ k ) {
 for ( l = 0 ;
 l < BAND_COEFF_CONTEXTS ( k ) ;
 ++ l ) {
 for ( t = 0 ;
 t < entropy_nodes_update ;
 ++ t ) {
 vp9_prob newp = new_coef_probs [ i ] [ j ] [ k ] [ l ] [ t ] ;
 vp9_prob * oldp = old_coef_probs [ i ] [ j ] [ k ] [ l ] + t ;
 int s ;
 int u = 0 ;
 if ( l >= prev_coef_contexts_to_update || k >= coef_band_to_update ) {
 u = 0 ;
 }
 else {
 if ( t == PIVOT_NODE ) s = vp9_prob_diff_update_savings_search_model ( frame_branch_ct [ i ] [ j ] [ k ] [ l ] [ 0 ] , old_coef_probs [ i ] [ j ] [ k ] [ l ] , & newp , upd ) ;
 else s = vp9_prob_diff_update_savings_search ( frame_branch_ct [ i ] [ j ] [ k ] [ l ] [ t ] , * oldp , & newp , upd ) ;
 if ( s > 0 && newp != * oldp ) u = 1 ;
 }
 updates += u ;
 if ( u == 0 && updates == 0 ) {
 noupdates_before_first ++ ;
 continue ;
 }
 if ( u == 1 && updates == 1 ) {
 int v ;
 vp9_write_bit ( bc , 1 ) ;
 for ( v = 0 ;
 v < noupdates_before_first ;
 ++ v ) vp9_write ( bc , 0 , upd ) ;
 }
 vp9_write ( bc , u , upd ) ;
 if ( u ) {
 vp9_write_prob_diff_update ( bc , newp , * oldp ) ;
 * oldp = newp ;
 }
 }
 }
 }
 }
 }
 if ( updates == 0 ) {
 vp9_write_bit ( bc , 0 ) ;
 }
 return ;
 }
 default : assert ( 0 ) ;
 }
 }