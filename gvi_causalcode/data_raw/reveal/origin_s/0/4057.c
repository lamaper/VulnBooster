void vp9_setup_pred_block ( const MACROBLOCKD * xd , struct buf_2d dst [ MAX_MB_PLANE ] , const YV12_BUFFER_CONFIG * src , int mi_row , int mi_col , const struct scale_factors * scale , const struct scale_factors * scale_uv ) {
 int i ;
 dst [ 0 ] . buf = src -> y_buffer ;
 dst [ 0 ] . stride = src -> y_stride ;
 dst [ 1 ] . buf = src -> u_buffer ;
 dst [ 2 ] . buf = src -> v_buffer ;
 dst [ 1 ] . stride = dst [ 2 ] . stride = src -> uv_stride ;
 for ( i = 0 ;
 i < MAX_MB_PLANE ;
 ++ i ) {
 setup_pred_plane ( dst + i , dst [ i ] . buf , dst [ i ] . stride , mi_row , mi_col , i ? scale_uv : scale , xd -> plane [ i ] . subsampling_x , xd -> plane [ i ] . subsampling_y ) ;
 }
 }