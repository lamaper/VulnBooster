static void adjust_arnr_filter ( VP9_COMP * cpi , int distance , int group_boost , int * arnr_frames , int * arnr_strength ) {
 const VP9EncoderConfig * const oxcf = & cpi -> oxcf ;
 const int frames_after_arf = vp9_lookahead_depth ( cpi -> lookahead ) - distance - 1 ;
 int frames_fwd = ( cpi -> oxcf . arnr_max_frames - 1 ) >> 1 ;
 int frames_bwd ;
 int q , frames , strength ;
 if ( frames_fwd > frames_after_arf ) frames_fwd = frames_after_arf ;
 if ( frames_fwd > distance ) frames_fwd = distance ;
 frames_bwd = frames_fwd ;
 if ( frames_bwd < distance ) frames_bwd += ( oxcf -> arnr_max_frames + 1 ) & 0x1 ;
 frames = frames_bwd + 1 + frames_fwd ;
 if ( cpi -> common . current_video_frame > 1 ) q = ( ( int ) vp9_convert_qindex_to_q ( cpi -> rc . avg_frame_qindex [ INTER_FRAME ] ) ) ;
 else q = ( ( int ) vp9_convert_qindex_to_q ( cpi -> rc . avg_frame_qindex [ KEY_FRAME ] ) ) ;
 if ( q > 16 ) {
 strength = oxcf -> arnr_strength ;
 }
 else {
 strength = oxcf -> arnr_strength - ( ( 16 - q ) / 2 ) ;
 if ( strength < 0 ) strength = 0 ;
 }
 if ( frames > group_boost / 150 ) {
 frames = group_boost / 150 ;
 frames += ! ( frames & 1 ) ;
 }
 if ( strength > group_boost / 300 ) {
 strength = group_boost / 300 ;
 }
 if ( cpi -> oxcf . pass == 2 && cpi -> multi_arf_allowed ) {
 const GF_GROUP * const gf_group = & cpi -> twopass . gf_group ;
 if ( gf_group -> rf_level [ gf_group -> index ] != GF_ARF_STD ) {
 strength >>= 1 ;
 }
 }
 * arnr_frames = frames ;
 * arnr_strength = strength ;
 }