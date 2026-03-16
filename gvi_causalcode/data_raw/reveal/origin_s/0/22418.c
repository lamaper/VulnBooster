void vp9_setup_pre_planes ( MACROBLOCKD * xd , int idx , const YV12_BUFFER_CONFIG * src , int mi_row , int mi_col , const struct scale_factors * sf ) {
 if ( src != NULL ) {
 int i ;
 uint8_t * const buffers [ 4 ] = {
 src -> y_buffer , src -> u_buffer , src -> v_buffer , src -> alpha_buffer }
 ;
 const int strides [ 4 ] = {
 src -> y_stride , src -> uv_stride , src -> uv_stride , src -> alpha_stride }
 ;
 for ( i = 0 ;
 i < MAX_MB_PLANE ;
 ++ i ) {
 struct macroblockd_plane * const pd = & xd -> plane [ i ] ;
 setup_pred_plane ( & pd -> pre [ idx ] , buffers [ i ] , strides [ i ] , mi_row , mi_col , sf , pd -> subsampling_x , pd -> subsampling_y ) ;
 }
 }
 }