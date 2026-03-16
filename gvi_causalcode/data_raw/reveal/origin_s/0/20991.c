static int vdpau_h264_end_frame ( AVCodecContext * avctx ) {
 AVVDPAUContext * hwctx = avctx -> hwaccel_context ;
 H264Context * h = avctx -> priv_data ;
 VdpVideoSurface surf = ff_vdpau_get_surface_id ( h -> cur_pic_ptr ) ;
 hwctx -> render ( hwctx -> decoder , surf , ( void * ) & hwctx -> info , hwctx -> bitstream_buffers_used , hwctx -> bitstream_buffers ) ;
 ff_h264_draw_horiz_band ( h , 0 , h -> avctx -> height ) ;
 hwctx -> bitstream_buffers_used = 0 ;
 return 0 ;
 }