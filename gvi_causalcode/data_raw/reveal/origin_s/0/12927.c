void vp9_setup_src_planes ( MACROBLOCK * x , const YV12_BUFFER_CONFIG * src , int mi_row , int mi_col ) {
 uint8_t * const buffers [ 3 ] = {
 src -> y_buffer , src -> u_buffer , src -> v_buffer }
 ;
 const int strides [ 3 ] = {
 src -> y_stride , src -> uv_stride , src -> uv_stride }
 ;
 int i ;
 x -> e_mbd . cur_buf = src ;
 for ( i = 0 ;
 i < MAX_MB_PLANE ;
 i ++ ) setup_pred_plane ( & x -> plane [ i ] . src , buffers [ i ] , strides [ i ] , mi_row , mi_col , NULL , x -> e_mbd . plane [ i ] . subsampling_x , x -> e_mbd . plane [ i ] . subsampling_y ) ;
 }