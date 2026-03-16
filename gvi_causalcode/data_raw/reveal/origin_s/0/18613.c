static int vdpau_h264_decode_slice ( AVCodecContext * avctx , const uint8_t * buffer , uint32_t size ) {
 AVVDPAUContext * hwctx = avctx -> hwaccel_context ;
 int val ;
 val = ff_vdpau_add_buffer ( avctx , start_code_prefix , 3 ) ;
 if ( val ) return val ;
 val = ff_vdpau_add_buffer ( avctx , buffer , size ) ;
 if ( val ) return val ;
 hwctx -> info . h264 . slice_count ++ ;
 return 0 ;
 }