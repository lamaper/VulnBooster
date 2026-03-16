void vp9_loop_filter_frame ( YV12_BUFFER_CONFIG * frame , VP9_COMMON * cm , MACROBLOCKD * xd , int frame_filter_level , int y_only , int partial_frame ) {
 int start_mi_row , end_mi_row , mi_rows_to_filter ;
 if ( ! frame_filter_level ) return ;
 start_mi_row = 0 ;
 mi_rows_to_filter = cm -> mi_rows ;
 if ( partial_frame && cm -> mi_rows > 8 ) {
 start_mi_row = cm -> mi_rows >> 1 ;
 start_mi_row &= 0xfffffff8 ;
 mi_rows_to_filter = MAX ( cm -> mi_rows / 8 , 8 ) ;
 }
 end_mi_row = start_mi_row + mi_rows_to_filter ;
 vp9_loop_filter_frame_init ( cm , frame_filter_level ) ;
 vp9_loop_filter_rows ( frame , cm , xd -> plane , start_mi_row , end_mi_row , y_only ) ;
 }