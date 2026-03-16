void ff_h264_filter_mb_fast ( H264Context * h , int mb_x , int mb_y , uint8_t * img_y , uint8_t * img_cb , uint8_t * img_cr , unsigned int linesize , unsigned int uvlinesize ) {
 assert ( ! FRAME_MBAFF ) ;
 if ( ! h -> h264dsp . h264_loop_filter_strength || h -> pps . chroma_qp_diff ) {
 ff_h264_filter_mb ( h , mb_x , mb_y , img_y , img_cb , img_cr , linesize , uvlinesize ) ;
 return ;
 }


 h264_filter_mb_fast_internal ( h , mb_x , mb_y , img_y , img_cb , img_cr , linesize , uvlinesize , 1 ) ;
 }
 else {
 h264_filter_mb_fast_internal ( h , mb_x , mb_y , img_y , img_cb , img_cr , linesize , uvlinesize , 0 ) ;
 }
