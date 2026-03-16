static void allocate_gf_group_bits ( VP9_COMP * cpi , int64_t gf_group_bits , double group_error , int gf_arf_bits ) {
 RATE_CONTROL * const rc = & cpi -> rc ;
 const VP9EncoderConfig * const oxcf = & cpi -> oxcf ;
 TWO_PASS * const twopass = & cpi -> twopass ;
 GF_GROUP * const gf_group = & twopass -> gf_group ;
 FIRSTPASS_STATS frame_stats ;
 int i ;
 int frame_index = 1 ;
 int target_frame_size ;
 int key_frame ;
 const int max_bits = frame_max_bits ( & cpi -> rc , & cpi -> oxcf ) ;
 int64_t total_group_bits = gf_group_bits ;
 double modified_err = 0.0 ;
 double err_fraction ;
 int mid_boost_bits = 0 ;
 int mid_frame_idx ;
 unsigned char arf_buffer_indices [ MAX_ACTIVE_ARFS ] ;
 int alt_frame_index = frame_index ;
 int has_temporal_layers = is_two_pass_svc ( cpi ) && cpi -> svc . number_temporal_layers > 1 ;
 if ( has_temporal_layers ) alt_frame_index = cpi -> svc . number_temporal_layers ;
 key_frame = cpi -> common . frame_type == KEY_FRAME || vp9_is_upper_layer_key_frame ( cpi ) ;
 get_arf_buffer_indices ( arf_buffer_indices ) ;
 if ( ! key_frame ) {
 if ( rc -> source_alt_ref_active ) {
 gf_group -> update_type [ 0 ] = OVERLAY_UPDATE ;
 gf_group -> rf_level [ 0 ] = INTER_NORMAL ;
 gf_group -> bit_allocation [ 0 ] = 0 ;
 gf_group -> arf_update_idx [ 0 ] = arf_buffer_indices [ 0 ] ;
 gf_group -> arf_ref_idx [ 0 ] = arf_buffer_indices [ 0 ] ;
 }
 else {
 gf_group -> update_type [ 0 ] = GF_UPDATE ;
 gf_group -> rf_level [ 0 ] = GF_ARF_STD ;
 gf_group -> bit_allocation [ 0 ] = gf_arf_bits ;
 gf_group -> arf_update_idx [ 0 ] = arf_buffer_indices [ 0 ] ;
 gf_group -> arf_ref_idx [ 0 ] = arf_buffer_indices [ 0 ] ;
 }
 if ( EOF == input_stats ( twopass , & frame_stats ) ) return ;
 }
 if ( rc -> source_alt_ref_pending || ! key_frame ) total_group_bits -= gf_arf_bits ;
 if ( rc -> source_alt_ref_pending ) {
 gf_group -> update_type [ alt_frame_index ] = ARF_UPDATE ;
 gf_group -> rf_level [ alt_frame_index ] = GF_ARF_STD ;
 gf_group -> bit_allocation [ alt_frame_index ] = gf_arf_bits ;
 if ( has_temporal_layers ) gf_group -> arf_src_offset [ alt_frame_index ] = ( unsigned char ) ( rc -> baseline_gf_interval - cpi -> svc . number_temporal_layers ) ;
 else gf_group -> arf_src_offset [ alt_frame_index ] = ( unsigned char ) ( rc -> baseline_gf_interval - 1 ) ;
 gf_group -> arf_update_idx [ alt_frame_index ] = arf_buffer_indices [ 0 ] ;
 gf_group -> arf_ref_idx [ alt_frame_index ] = arf_buffer_indices [ cpi -> multi_arf_last_grp_enabled && rc -> source_alt_ref_active ] ;
 if ( ! has_temporal_layers ) ++ frame_index ;
 if ( cpi -> multi_arf_enabled ) {
 gf_group -> update_type [ frame_index ] = ARF_UPDATE ;
 gf_group -> rf_level [ frame_index ] = GF_ARF_LOW ;
 gf_group -> arf_src_offset [ frame_index ] = ( unsigned char ) ( ( rc -> baseline_gf_interval >> 1 ) - 1 ) ;
 gf_group -> arf_update_idx [ frame_index ] = arf_buffer_indices [ 1 ] ;
 gf_group -> arf_ref_idx [ frame_index ] = arf_buffer_indices [ 0 ] ;
 ++ frame_index ;
 }
 }
 mid_frame_idx = frame_index + ( rc -> baseline_gf_interval >> 1 ) - 1 ;
 for ( i = 0 ;
 i < rc -> baseline_gf_interval - 1 ;
 ++ i ) {
 int arf_idx = 0 ;
 if ( EOF == input_stats ( twopass , & frame_stats ) ) break ;
 if ( has_temporal_layers && frame_index == alt_frame_index ) {
 ++ frame_index ;
 }
 modified_err = calculate_modified_err ( twopass , oxcf , & frame_stats ) ;
 if ( group_error > 0 ) err_fraction = modified_err / DOUBLE_DIVIDE_CHECK ( group_error ) ;
 else err_fraction = 0.0 ;
 target_frame_size = ( int ) ( ( double ) total_group_bits * err_fraction ) ;
 if ( rc -> source_alt_ref_pending && cpi -> multi_arf_enabled ) {
 mid_boost_bits += ( target_frame_size >> 4 ) ;
 target_frame_size -= ( target_frame_size >> 4 ) ;
 if ( frame_index <= mid_frame_idx ) arf_idx = 1 ;
 }
 gf_group -> arf_update_idx [ frame_index ] = arf_buffer_indices [ arf_idx ] ;
 gf_group -> arf_ref_idx [ frame_index ] = arf_buffer_indices [ arf_idx ] ;
 target_frame_size = clamp ( target_frame_size , 0 , MIN ( max_bits , ( int ) total_group_bits ) ) ;
 gf_group -> update_type [ frame_index ] = LF_UPDATE ;
 gf_group -> rf_level [ frame_index ] = INTER_NORMAL ;
 gf_group -> bit_allocation [ frame_index ] = target_frame_size ;
 ++ frame_index ;
 }
 gf_group -> arf_update_idx [ frame_index ] = arf_buffer_indices [ 0 ] ;
 gf_group -> arf_ref_idx [ frame_index ] = arf_buffer_indices [ 0 ] ;
 if ( rc -> source_alt_ref_pending ) {
 gf_group -> update_type [ frame_index ] = OVERLAY_UPDATE ;
 gf_group -> rf_level [ frame_index ] = INTER_NORMAL ;
 if ( cpi -> multi_arf_enabled ) {
 gf_group -> bit_allocation [ 2 ] = gf_group -> bit_allocation [ mid_frame_idx ] + mid_boost_bits ;
 gf_group -> update_type [ mid_frame_idx ] = OVERLAY_UPDATE ;
 gf_group -> bit_allocation [ mid_frame_idx ] = 0 ;
 }
 }
 else {
 gf_group -> update_type [ frame_index ] = GF_UPDATE ;
 gf_group -> rf_level [ frame_index ] = GF_ARF_STD ;
 }
 cpi -> multi_arf_last_grp_enabled = cpi -> multi_arf_enabled ;
 }