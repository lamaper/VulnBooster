void vp9_setup_dst_planes ( struct macroblockd_plane planes [ MAX_MB_PLANE ] , const YV12_BUFFER_CONFIG * src , int mi_row , int mi_col ) {
 uint8_t * const buffers [ 4 ] = {
 src -> y_buffer , src -> u_buffer , src -> v_buffer , src -> alpha_buffer }
 ;
 const int strides [ 4 ] = {
 src -> y_stride , src -> uv_stride , src -> uv_stride , src -> alpha_stride }
 ;
 int i ;
 for ( i = 0 ;
 i < MAX_MB_PLANE ;
 ++ i ) {
 struct macroblockd_plane * const pd = & planes [ i ] ;
 setup_pred_plane ( & pd -> dst , buffers [ i ] , strides [ i ] , mi_row , mi_col , NULL , pd -> subsampling_x , pd -> subsampling_y ) ;
 }
 }