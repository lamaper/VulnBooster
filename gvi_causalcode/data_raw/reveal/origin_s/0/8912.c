static int rc_pick_q_and_bounds_two_pass ( const VP9_COMP * cpi , int * bottom_index , int * top_index ) {
 const VP9_COMMON * const cm = & cpi -> common ;
 const RATE_CONTROL * const rc = & cpi -> rc ;
 const VP9EncoderConfig * const oxcf = & cpi -> oxcf ;
 const int cq_level = get_active_cq_level ( rc , oxcf ) ;
 int active_best_quality ;
 int active_worst_quality = cpi -> twopass . active_worst_quality ;
 int q ;
 int * inter_minq ;
 ASSIGN_MINQ_TABLE ( cm -> bit_depth , inter_minq ) ;
 if ( frame_is_intra_only ( cm ) || vp9_is_upper_layer_key_frame ( cpi ) ) {
 if ( rc -> this_key_frame_forced ) {
 double last_boosted_q ;
 int delta_qindex ;
 int qindex ;
 if ( cpi -> twopass . last_kfgroup_zeromotion_pct >= STATIC_MOTION_THRESH ) {
 qindex = MIN ( rc -> last_kf_qindex , rc -> last_boosted_qindex ) ;
 active_best_quality = qindex ;
 last_boosted_q = vp9_convert_qindex_to_q ( qindex , cm -> bit_depth ) ;
 delta_qindex = vp9_compute_qdelta ( rc , last_boosted_q , last_boosted_q * 1.25 , cm -> bit_depth ) ;
 active_worst_quality = MIN ( qindex + delta_qindex , active_worst_quality ) ;
 }
 else {
 qindex = rc -> last_boosted_qindex ;
 last_boosted_q = vp9_convert_qindex_to_q ( qindex , cm -> bit_depth ) ;
 delta_qindex = vp9_compute_qdelta ( rc , last_boosted_q , last_boosted_q * 0.75 , cm -> bit_depth ) ;
 active_best_quality = MAX ( qindex + delta_qindex , rc -> best_quality ) ;
 }
 }
 else {
 double q_adj_factor = 1.0 ;
 double q_val ;
 active_best_quality = get_kf_active_quality ( rc , active_worst_quality , cm -> bit_depth ) ;
 if ( ( cm -> width * cm -> height ) <= ( 352 * 288 ) ) {
 q_adj_factor -= 0.25 ;
 }
 q_adj_factor += 0.05 - ( 0.001 * ( double ) cpi -> twopass . kf_zeromotion_pct ) ;
 q_val = vp9_convert_qindex_to_q ( active_best_quality , cm -> bit_depth ) ;
 active_best_quality += vp9_compute_qdelta ( rc , q_val , q_val * q_adj_factor , cm -> bit_depth ) ;
 }
 }
 else if ( ! rc -> is_src_frame_alt_ref && ( cpi -> refresh_golden_frame || cpi -> refresh_alt_ref_frame ) ) {
 if ( rc -> frames_since_key > 1 && rc -> avg_frame_qindex [ INTER_FRAME ] < active_worst_quality ) {
 q = rc -> avg_frame_qindex [ INTER_FRAME ] ;
 }
 else {
 q = active_worst_quality ;
 }
 if ( oxcf -> rc_mode == VPX_CQ ) {
 if ( q < cq_level ) q = cq_level ;
 active_best_quality = get_gf_active_quality ( rc , q , cm -> bit_depth ) ;
 active_best_quality = active_best_quality * 15 / 16 ;
 }
 else if ( oxcf -> rc_mode == VPX_Q ) {
 if ( ! cpi -> refresh_alt_ref_frame ) {
 active_best_quality = cq_level ;
 }
 else {
 active_best_quality = get_gf_active_quality ( rc , q , cm -> bit_depth ) ;
 }
 }
 else {
 active_best_quality = get_gf_active_quality ( rc , q , cm -> bit_depth ) ;
 }
 }
 else {
 if ( oxcf -> rc_mode == VPX_Q ) {
 active_best_quality = cq_level ;
 }
 else {
 active_best_quality = inter_minq [ active_worst_quality ] ;
 if ( ( oxcf -> rc_mode == VPX_CQ ) && ( active_best_quality < cq_level ) ) {
 active_best_quality = cq_level ;
 }
 }
 }

 if ( ! ( ( frame_is_intra_only ( cm ) || vp9_is_upper_layer_key_frame ( cpi ) ) ) || ! rc -> this_key_frame_forced || ( cpi -> twopass . last_kfgroup_zeromotion_pct < STATIC_MOTION_THRESH ) ) {
 const GF_GROUP * const gf_group = & cpi -> twopass . gf_group ;
 const double rate_factor_deltas [ RATE_FACTOR_LEVELS ] = {
 1.00 , 1.00 , 1.50 , 1.75 , 2.00 , }
 ;
 const double rate_factor = rate_factor_deltas [ gf_group -> rf_level [ gf_group -> index ] ] ;
 int qdelta = vp9_compute_qdelta_by_rate ( & cpi -> rc , cm -> frame_type , active_worst_quality , rate_factor , cm -> bit_depth ) ;
 active_worst_quality = active_worst_quality + qdelta ;
 active_worst_quality = MAX ( active_worst_quality , active_best_quality ) ;
 }

 active_worst_quality = clamp ( active_worst_quality , active_best_quality , rc -> worst_quality ) ;
 if ( oxcf -> rc_mode == VPX_Q ) {
 q = active_best_quality ;
 }
 else if ( ( frame_is_intra_only ( cm ) || vp9_is_upper_layer_key_frame ( cpi ) ) && rc -> this_key_frame_forced ) {
 if ( cpi -> twopass . last_kfgroup_zeromotion_pct >= STATIC_MOTION_THRESH ) {
 q = MIN ( rc -> last_kf_qindex , rc -> last_boosted_qindex ) ;
 }
 else {
 q = rc -> last_boosted_qindex ;
 }
 }
 else {
 q = vp9_rc_regulate_q ( cpi , rc -> this_frame_target , active_best_quality , active_worst_quality ) ;
 if ( q > active_worst_quality ) {
 if ( rc -> this_frame_target >= rc -> max_frame_bandwidth ) active_worst_quality = q ;
 else q = active_worst_quality ;
 }
 }
 clamp ( q , active_best_quality , active_worst_quality ) ;
 * top_index = active_worst_quality ;
 * bottom_index = active_best_quality ;
 assert ( * top_index <= rc -> worst_quality && * top_index >= rc -> best_quality ) ;
 assert ( * bottom_index <= rc -> worst_quality && * bottom_index >= rc -> best_quality ) ;
 assert ( q <= rc -> worst_quality && q >= rc -> best_quality ) ;
 return q ;
 }