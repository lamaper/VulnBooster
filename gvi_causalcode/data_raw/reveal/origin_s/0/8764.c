static void read_bitdepth_colorspace_sampling ( VP9_COMMON * cm , struct vp9_read_bit_buffer * rb ) {
 if ( cm -> profile >= PROFILE_2 ) cm -> bit_depth = vp9_rb_read_bit ( rb ) ? VPX_BITS_12 : VPX_BITS_10 ;
 cm -> color_space = ( COLOR_SPACE ) vp9_rb_read_literal ( rb , 3 ) ;
 if ( cm -> color_space != SRGB ) {
 vp9_rb_read_bit ( rb ) ;
 if ( cm -> profile == PROFILE_1 || cm -> profile == PROFILE_3 ) {
 cm -> subsampling_x = vp9_rb_read_bit ( rb ) ;
 cm -> subsampling_y = vp9_rb_read_bit ( rb ) ;
 if ( cm -> subsampling_x == 1 && cm -> subsampling_y == 1 ) vpx_internal_error ( & cm -> error , VPX_CODEC_UNSUP_BITSTREAM , "4:2:0 color not supported in profile 1 or 3" ) ;
 if ( vp9_rb_read_bit ( rb ) ) vpx_internal_error ( & cm -> error , VPX_CODEC_UNSUP_BITSTREAM , "Reserved bit set" ) ;
 }
 else {
 cm -> subsampling_y = cm -> subsampling_x = 1 ;
 }
 }
 else {
 if ( cm -> profile == PROFILE_1 || cm -> profile == PROFILE_3 ) {
 cm -> subsampling_y = cm -> subsampling_x = 0 ;
 if ( vp9_rb_read_bit ( rb ) ) vpx_internal_error ( & cm -> error , VPX_CODEC_UNSUP_BITSTREAM , "Reserved bit set" ) ;
 }
 else {
 vpx_internal_error ( & cm -> error , VPX_CODEC_UNSUP_BITSTREAM , "4:4:4 color not supported in profile 0 or 2" ) ;
 }
 }
 }