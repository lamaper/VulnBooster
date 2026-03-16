static void scale_and_extend_frame_nonnormative ( const YV12_BUFFER_CONFIG * src , YV12_BUFFER_CONFIG * dst ) {
 int i ;
 const uint8_t * const srcs [ 3 ] = {
 src -> y_buffer , src -> u_buffer , src -> v_buffer }
 ;
 const int src_strides [ 3 ] = {
 src -> y_stride , src -> uv_stride , src -> uv_stride }
 ;
 const int src_widths [ 3 ] = {
 src -> y_crop_width , src -> uv_crop_width , src -> uv_crop_width }
 ;
 const int src_heights [ 3 ] = {
 src -> y_crop_height , src -> uv_crop_height , src -> uv_crop_height }
 ;
 uint8_t * const dsts [ 3 ] = {
 dst -> y_buffer , dst -> u_buffer , dst -> v_buffer }
 ;
 const int dst_strides [ 3 ] = {
 dst -> y_stride , dst -> uv_stride , dst -> uv_stride }
 ;
 const int dst_widths [ 3 ] = {
 dst -> y_crop_width , dst -> uv_crop_width , dst -> uv_crop_width }
 ;
 const int dst_heights [ 3 ] = {
 dst -> y_crop_height , dst -> uv_crop_height , dst -> uv_crop_height }
 ;
 for ( i = 0 ;
 i < MAX_MB_PLANE ;
 ++ i ) vp9_resize_plane ( srcs [ i ] , src_heights [ i ] , src_widths [ i ] , src_strides [ i ] , dsts [ i ] , dst_heights [ i ] , dst_widths [ i ] , dst_strides [ i ] ) ;
 vp9_extend_frame_borders ( dst ) ;
 }