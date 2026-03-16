int release_vp9_frame_buffer ( void * cb_priv , vpx_codec_frame_buffer_t * fb ) {
 struct ExternalFrameBuffer * const ext_fb = ( struct ExternalFrameBuffer * ) fb -> priv ;
 ( void ) cb_priv ;
 ext_fb -> in_use = 0 ;
 return 0 ;
 }