static void encode_with_recode_loop ( VP9_COMP * cpi , size_t * size , uint8_t * dest , int q , int bottom_index , int top_index ) {
 VP9_COMMON * const cm = & cpi -> common ;
 RATE_CONTROL * const rc = & cpi -> rc ;
 int loop_count = 0 ;
 int loop = 0 ;
 int overshoot_seen = 0 ;
 int undershoot_seen = 0 ;
 int q_low = bottom_index , q_high = top_index ;
 int frame_over_shoot_limit ;
 int frame_under_shoot_limit ;
 vp9_rc_compute_frame_size_bounds ( cpi , rc -> this_frame_target , & frame_under_shoot_limit , & frame_over_shoot_limit ) ;
 do {
 vp9_clear_system_state ( ) ;
 vp9_set_quantizer ( cm , q ) ;
 if ( loop_count == 0 ) setup_frame ( cpi ) ;
 if ( cpi -> oxcf . aq_mode == VARIANCE_AQ ) {
 vp9_vaq_frame_setup ( cpi ) ;
 }
 else if ( cpi -> oxcf . aq_mode == COMPLEXITY_AQ ) {
 vp9_setup_in_frame_q_adj ( cpi ) ;
 }
 vp9_encode_frame ( cpi ) ;
 vp9_clear_system_state ( ) ;
 if ( cpi -> sf . recode_loop >= ALLOW_RECODE_KFARFGF ) {
 save_coding_context ( cpi ) ;
 if ( ! cpi -> sf . use_nonrd_pick_mode ) vp9_pack_bitstream ( cpi , dest , size ) ;
 rc -> projected_frame_size = ( int ) ( * size ) << 3 ;
 restore_coding_context ( cpi ) ;
 if ( frame_over_shoot_limit == 0 ) frame_over_shoot_limit = 1 ;
 }
 if ( cpi -> oxcf . rc_mode == VPX_Q ) {
 loop = 0 ;
 }
 else {
 if ( ( cm -> frame_type == KEY_FRAME ) && rc -> this_key_frame_forced && ( rc -> projected_frame_size < rc -> max_frame_bandwidth ) ) {
 int last_q = q ;
 int kf_err = vp9_get_y_sse ( cpi -> Source , get_frame_new_buffer ( cm ) ) ;
 int high_err_target = cpi -> ambient_err ;
 int low_err_target = cpi -> ambient_err >> 1 ;
 kf_err += ! kf_err ;
 if ( ( kf_err > high_err_target && rc -> projected_frame_size <= frame_over_shoot_limit ) || ( kf_err > low_err_target && rc -> projected_frame_size <= frame_under_shoot_limit ) ) {
 q_high = q > q_low ? q - 1 : q_low ;
 q = ( q * high_err_target ) / kf_err ;
 q = MIN ( q , ( q_high + q_low ) >> 1 ) ;
 }
 else if ( kf_err < low_err_target && rc -> projected_frame_size >= frame_under_shoot_limit ) {
 q_low = q < q_high ? q + 1 : q_high ;
 q = ( q * low_err_target ) / kf_err ;
 q = MIN ( q , ( q_high + q_low + 1 ) >> 1 ) ;
 }
 q = clamp ( q , q_low , q_high ) ;
 loop = q != last_q ;
 }
 else if ( recode_loop_test ( cpi , frame_over_shoot_limit , frame_under_shoot_limit , q , MAX ( q_high , top_index ) , bottom_index ) ) {
 int last_q = q ;
 int retries = 0 ;
 if ( rc -> projected_frame_size > rc -> this_frame_target ) {
 if ( rc -> projected_frame_size >= rc -> max_frame_bandwidth ) q_high = rc -> worst_quality ;
 q_low = q < q_high ? q + 1 : q_high ;
 if ( undershoot_seen || loop_count > 1 ) {
 vp9_rc_update_rate_correction_factors ( cpi , 1 ) ;
 q = ( q_high + q_low + 1 ) / 2 ;
 }
 else {
 vp9_rc_update_rate_correction_factors ( cpi , 0 ) ;
 q = vp9_rc_regulate_q ( cpi , rc -> this_frame_target , bottom_index , MAX ( q_high , top_index ) ) ;
 while ( q < q_low && retries < 10 ) {
 vp9_rc_update_rate_correction_factors ( cpi , 0 ) ;
 q = vp9_rc_regulate_q ( cpi , rc -> this_frame_target , bottom_index , MAX ( q_high , top_index ) ) ;
 retries ++ ;
 }
 }
 overshoot_seen = 1 ;
 }
 else {
 q_high = q > q_low ? q - 1 : q_low ;
 if ( overshoot_seen || loop_count > 1 ) {
 vp9_rc_update_rate_correction_factors ( cpi , 1 ) ;
 q = ( q_high + q_low ) / 2 ;
 }
 else {
 vp9_rc_update_rate_correction_factors ( cpi , 0 ) ;
 q = vp9_rc_regulate_q ( cpi , rc -> this_frame_target , bottom_index , top_index ) ;
 if ( cpi -> oxcf . rc_mode == VPX_CQ && q < q_low ) {
 q_low = q ;
 }
 while ( q > q_high && retries < 10 ) {
 vp9_rc_update_rate_correction_factors ( cpi , 0 ) ;
 q = vp9_rc_regulate_q ( cpi , rc -> this_frame_target , bottom_index , top_index ) ;
 retries ++ ;
 }
 }
 undershoot_seen = 1 ;
 }
 q = clamp ( q , q_low , q_high ) ;
 loop = q != last_q ;
 }
 else {
 loop = 0 ;
 }
 }
 if ( rc -> is_src_frame_alt_ref && rc -> projected_frame_size < rc -> max_frame_bandwidth ) loop = 0 ;
 if ( loop ) {
 loop_count ++ ;


 }
 while ( loop ) ;
 }