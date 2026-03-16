static void set_segment_id ( VP9_COMMON * cm , BLOCK_SIZE bsize , int mi_row , int mi_col , int segment_id ) {
 const int mi_offset = mi_row * cm -> mi_cols + mi_col ;
 const int bw = num_8x8_blocks_wide_lookup [ bsize ] ;
 const int bh = num_8x8_blocks_high_lookup [ bsize ] ;
 const int xmis = MIN ( cm -> mi_cols - mi_col , bw ) ;
 const int ymis = MIN ( cm -> mi_rows - mi_row , bh ) ;
 int x , y ;
 assert ( segment_id >= 0 && segment_id < MAX_SEGMENTS ) ;
 for ( y = 0 ;
 y < ymis ;
 y ++ ) for ( x = 0 ;
 x < xmis ;
 x ++ ) cm -> last_frame_seg_map [ mi_offset + y * cm -> mi_cols + x ] = segment_id ;
 }