int vp9_release_frame_buffer ( void * cb_priv , vpx_codec_frame_buffer_t * fb ) {
 InternalFrameBuffer * const int_fb = ( InternalFrameBuffer * ) fb -> priv ;
 ( void ) cb_priv ;
 if ( int_fb ) int_fb -> in_use = 0 ;
 return 0 ;
 }