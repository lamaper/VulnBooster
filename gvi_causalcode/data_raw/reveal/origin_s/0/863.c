static void write_frame_size_with_refs ( VP9_COMP * cpi , struct vp9_write_bit_buffer * wb ) {
 VP9_COMMON * const cm = & cpi -> common ;
 int found = 0 ;
 MV_REFERENCE_FRAME ref_frame ;
 for ( ref_frame = LAST_FRAME ;
 ref_frame <= ALTREF_FRAME ;
 ++ ref_frame ) {
 YV12_BUFFER_CONFIG * cfg = get_ref_frame_buffer ( cpi , ref_frame ) ;
 found = cm -> width == cfg -> y_crop_width && cm -> height == cfg -> y_crop_height ;
 if ( cpi -> use_svc && ( ( cpi -> svc . number_temporal_layers > 1 && cpi -> oxcf . rc_mode == VPX_CBR ) || ( cpi -> svc . number_spatial_layers > 1 && cpi -> svc . layer_context [ cpi -> svc . spatial_layer_id ] . is_key_frame ) ) ) {
 found = 0 ;
 }
 vp9_wb_write_bit ( wb , found ) ;
 if ( found ) {
 break ;
 }
 }
 if ( ! found ) {
 vp9_wb_write_literal ( wb , cm -> width - 1 , 16 ) ;
 vp9_wb_write_literal ( wb , cm -> height - 1 , 16 ) ;
 }
 write_display_size ( cm , wb ) ;
 }