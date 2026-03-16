static void setup_features ( VP8_COMP * cpi ) {
 if ( cpi -> mb . e_mbd . segmentation_enabled ) {
 cpi -> mb . e_mbd . update_mb_segmentation_map = 1 ;
 cpi -> mb . e_mbd . update_mb_segmentation_data = 1 ;
 }
 else {
 cpi -> mb . e_mbd . update_mb_segmentation_map = 0 ;
 cpi -> mb . e_mbd . update_mb_segmentation_data = 0 ;
 }
 cpi -> mb . e_mbd . mode_ref_lf_delta_enabled = 0 ;
 cpi -> mb . e_mbd . mode_ref_lf_delta_update = 0 ;
 vpx_memset ( cpi -> mb . e_mbd . ref_lf_deltas , 0 , sizeof ( cpi -> mb . e_mbd . ref_lf_deltas ) ) ;
 vpx_memset ( cpi -> mb . e_mbd . mode_lf_deltas , 0 , sizeof ( cpi -> mb . e_mbd . mode_lf_deltas ) ) ;
 vpx_memset ( cpi -> mb . e_mbd . last_ref_lf_deltas , 0 , sizeof ( cpi -> mb . e_mbd . ref_lf_deltas ) ) ;
 vpx_memset ( cpi -> mb . e_mbd . last_mode_lf_deltas , 0 , sizeof ( cpi -> mb . e_mbd . mode_lf_deltas ) ) ;
 set_default_lf_deltas ( cpi ) ;
 }