static void write_bitdepth_colorspace_sampling ( VP9_COMMON * const cm , struct vp9_write_bit_buffer * wb ) {
 if ( cm -> profile >= PROFILE_2 ) {
 assert ( cm -> bit_depth > VPX_BITS_8 ) ;
 vp9_wb_write_bit ( wb , cm -> bit_depth == VPX_BITS_10 ? 0 : 1 ) ;
 }
 vp9_wb_write_literal ( wb , cm -> color_space , 3 ) ;
 if ( cm -> color_space != SRGB ) {
 vp9_wb_write_bit ( wb , 0 ) ;
 if ( cm -> profile == PROFILE_1 || cm -> profile == PROFILE_3 ) {
 assert ( cm -> subsampling_x != 1 || cm -> subsampling_y != 1 ) ;
 vp9_wb_write_bit ( wb , cm -> subsampling_x ) ;
 vp9_wb_write_bit ( wb , cm -> subsampling_y ) ;
 vp9_wb_write_bit ( wb , 0 ) ;
 }
 else {
 assert ( cm -> subsampling_x == 1 && cm -> subsampling_y == 1 ) ;
 }
 }
 else {
 assert ( cm -> profile == PROFILE_1 || cm -> profile == PROFILE_3 ) ;
 vp9_wb_write_bit ( wb , 0 ) ;
 }
 }