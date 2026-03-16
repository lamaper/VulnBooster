static inline void svq3_mc_dir_part ( SVQ3Context * s , int x , int y , int width , int height , int mx , int my , int dxy , int thirdpel , int dir , int avg ) {
 H264Context * h = & s -> h ;
 const Picture * pic = ( dir == 0 ) ? s -> last_pic : s -> next_pic ;
 uint8_t * src , * dest ;
 int i , emu = 0 ;
 int blocksize = 2 - ( width >> 3 ) ;
 mx += x ;
 my += y ;
 if ( mx < 0 || mx >= s -> h_edge_pos - width - 1 || my < 0 || my >= s -> v_edge_pos - height - 1 ) {
 emu = 1 ;
 mx = av_clip ( mx , - 16 , s -> h_edge_pos - width + 15 ) ;
 my = av_clip ( my , - 16 , s -> v_edge_pos - height + 15 ) ;
 }
 dest = h -> cur_pic . f . data [ 0 ] + x + y * h -> linesize ;
 src = pic -> f . data [ 0 ] + mx + my * h -> linesize ;
 if ( emu ) {
 h -> vdsp . emulated_edge_mc ( h -> edge_emu_buffer , src , h -> linesize , width + 1 , height + 1 , mx , my , s -> h_edge_pos , s -> v_edge_pos ) ;
 src = h -> edge_emu_buffer ;
 }
 if ( thirdpel ) ( avg ? h -> dsp . avg_tpel_pixels_tab : h -> dsp . put_tpel_pixels_tab ) [ dxy ] ( dest , src , h -> linesize , width , height ) ;
 else ( avg ? h -> dsp . avg_pixels_tab : h -> dsp . put_pixels_tab ) [ blocksize ] [ dxy ] ( dest , src , h -> linesize , height ) ;
 if ( ! ( h -> flags & CODEC_FLAG_GRAY ) ) {
 mx = mx + ( mx < ( int ) x ) >> 1 ;
 my = my + ( my < ( int ) y ) >> 1 ;
 width = width >> 1 ;
 height = height >> 1 ;
 blocksize ++ ;
 for ( i = 1 ;
 i < 3 ;
 i ++ ) {
 dest = h -> cur_pic . f . data [ i ] + ( x >> 1 ) + ( y >> 1 ) * h -> uvlinesize ;
 src = pic -> f . data [ i ] + mx + my * h -> uvlinesize ;
 if ( emu ) {
 h -> vdsp . emulated_edge_mc ( h -> edge_emu_buffer , src , h -> uvlinesize , width + 1 , height + 1 , mx , my , ( s -> h_edge_pos >> 1 ) , s -> v_edge_pos >> 1 ) ;
 src = h -> edge_emu_buffer ;
 }
 if ( thirdpel ) ( avg ? h -> dsp . avg_tpel_pixels_tab : h -> dsp . put_tpel_pixels_tab ) [ dxy ] ( dest , src , h -> uvlinesize , width , height ) ;
 else ( avg ? h -> dsp . avg_pixels_tab : h -> dsp . put_pixels_tab ) [ blocksize ] [ dxy ] ( dest , src , h -> uvlinesize , height ) ;
 }
 }
 }