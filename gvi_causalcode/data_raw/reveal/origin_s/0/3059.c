static void count_segs ( const VP9_COMMON * cm , MACROBLOCKD * xd , const TileInfo * tile , MODE_INFO * mi , int * no_pred_segcounts , int ( * temporal_predictor_count ) [ 2 ] , int * t_unpred_seg_counts , int bw , int bh , int mi_row , int mi_col ) {
 int segment_id ;
 if ( mi_row >= cm -> mi_rows || mi_col >= cm -> mi_cols ) return ;
 xd -> mi = mi ;
 segment_id = xd -> mi [ 0 ] . src_mi -> mbmi . segment_id ;
 set_mi_row_col ( xd , tile , mi_row , bh , mi_col , bw , cm -> mi_rows , cm -> mi_cols ) ;
 no_pred_segcounts [ segment_id ] ++ ;
 if ( cm -> frame_type != KEY_FRAME ) {
 const BLOCK_SIZE bsize = xd -> mi [ 0 ] . src_mi -> mbmi . sb_type ;
 const int pred_segment_id = vp9_get_segment_id ( cm , cm -> last_frame_seg_map , bsize , mi_row , mi_col ) ;
 const int pred_flag = pred_segment_id == segment_id ;
 const int pred_context = vp9_get_pred_context_seg_id ( xd ) ;
 xd -> mi [ 0 ] . src_mi -> mbmi . seg_id_predicted = pred_flag ;
 temporal_predictor_count [ pred_context ] [ pred_flag ] ++ ;
 if ( ! pred_flag ) t_unpred_seg_counts [ segment_id ] ++ ;
 }
 }