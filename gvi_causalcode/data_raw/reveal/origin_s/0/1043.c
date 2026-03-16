static void alloc_raw_frame_buffers ( VP8_COMP * cpi ) {

 int height = ( cpi -> oxcf . Height + 15 ) & ~ 15 ;

 if ( ! cpi -> lookahead ) vpx_internal_error ( & cpi -> common . error , VPX_CODEC_MEM_ERROR , "Failed to allocate lag buffers" ) ;

