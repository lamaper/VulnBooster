int vp9_get_segment_id ( const VP9_COMMON * cm , const uint8_t * segment_ids , BLOCK_SIZE bsize , int mi_row , int mi_col ) {
 const int mi_offset = mi_row * cm -> mi_cols + mi_col ;
 const int bw = num_8x8_blocks_wide_lookup [ bsize ] ;
 const int bh = num_8x8_blocks_high_lookup [ bsize ] ;
 const int xmis = MIN ( cm -> mi_cols - mi_col , bw ) ;
 const int ymis = MIN ( cm -> mi_rows - mi_row , bh ) ;
 int x , y , segment_id = INT_MAX ;
 for ( y = 0 ;
 y < ymis ;
 y ++ ) for ( x = 0 ;
 x < xmis ;
 x ++ ) segment_id = MIN ( segment_id , segment_ids [ mi_offset + y * cm -> mi_cols + x ] ) ;
 assert ( segment_id >= 0 && segment_id < MAX_SEGMENTS ) ;
 return segment_id ;
 }