int ff_vdpau_common_start_frame ( AVCodecContext * avctx , av_unused const uint8_t * buffer , av_unused uint32_t size ) {
 AVVDPAUContext * hwctx = avctx -> hwaccel_context ;
 hwctx -> bitstream_buffers_used = 0 ;
 return 0 ;
 }