static void init_config ( struct VP9_COMP * cpi , VP9EncoderConfig * oxcf ) {
 VP9_COMMON * const cm = & cpi -> common ;
 cpi -> oxcf = * oxcf ;
 cpi -> framerate = oxcf -> init_framerate ;
 cm -> profile = oxcf -> profile ;
 cm -> bit_depth = oxcf -> bit_depth ;
 cm -> color_space = UNKNOWN ;
 cm -> width = oxcf -> width ;
 cm -> height = oxcf -> height ;
 vp9_alloc_compressor_data ( cpi ) ;
 cpi -> svc . number_spatial_layers = oxcf -> ss_number_layers ;
 cpi -> svc . number_temporal_layers = oxcf -> ts_number_layers ;
 if ( ( cpi -> svc . number_temporal_layers > 1 && cpi -> oxcf . rc_mode == VPX_CBR ) || ( ( cpi -> svc . number_temporal_layers > 1 || cpi -> svc . number_spatial_layers > 1 ) && cpi -> oxcf . pass == 2 ) ) {
 vp9_init_layer_context ( cpi ) ;
 }
 vp9_change_config ( cpi , oxcf ) ;
 cpi -> static_mb_pct = 0 ;
 cpi -> ref_frame_flags = 0 ;
 init_buffer_indices ( cpi ) ;
 set_tile_limits ( cpi ) ;
 }