static void count_segs_sb ( const VP9_COMMON * cm , MACROBLOCKD * xd , const TileInfo * tile , MODE_INFO * * mi , int * no_pred_segcounts , int ( * temporal_predictor_count ) [ 2 ] , int * t_unpred_seg_counts , int mi_row , int mi_col , BLOCK_SIZE bsize ) {
 const int mis = cm -> mi_stride ;
 int bw , bh ;
 const int bs = num_8x8_blocks_wide_lookup [ bsize ] , hbs = bs / 2 ;
 if ( mi_row >= cm -> mi_rows || mi_col >= cm -> mi_cols ) return ;
 bw = num_8x8_blocks_wide_lookup [ mi [ 0 ] -> mbmi . sb_type ] ;
 bh = num_8x8_blocks_high_lookup [ mi [ 0 ] -> mbmi . sb_type ] ;
 if ( bw == bs && bh == bs ) {
 count_segs ( cm , xd , tile , mi , no_pred_segcounts , temporal_predictor_count , t_unpred_seg_counts , bs , bs , mi_row , mi_col ) ;
 }
 else if ( bw == bs && bh < bs ) {
 count_segs ( cm , xd , tile , mi , no_pred_segcounts , temporal_predictor_count , t_unpred_seg_counts , bs , hbs , mi_row , mi_col ) ;
 count_segs ( cm , xd , tile , mi + hbs * mis , no_pred_segcounts , temporal_predictor_count , t_unpred_seg_counts , bs , hbs , mi_row + hbs , mi_col ) ;
 }
 else if ( bw < bs && bh == bs ) {
 count_segs ( cm , xd , tile , mi , no_pred_segcounts , temporal_predictor_count , t_unpred_seg_counts , hbs , bs , mi_row , mi_col ) ;
 count_segs ( cm , xd , tile , mi + hbs , no_pred_segcounts , temporal_predictor_count , t_unpred_seg_counts , hbs , bs , mi_row , mi_col + hbs ) ;
 }
 else {
 const BLOCK_SIZE subsize = subsize_lookup [ PARTITION_SPLIT ] [ bsize ] ;
 int n ;
 assert ( bw < bs && bh < bs ) ;
 for ( n = 0 ;
 n < 4 ;
 n ++ ) {
 const int mi_dc = hbs * ( n & 1 ) ;
 const int mi_dr = hbs * ( n >> 1 ) ;
 count_segs_sb ( cm , xd , tile , & mi [ mi_dr * mis + mi_dc ] , no_pred_segcounts , temporal_predictor_count , t_unpred_seg_counts , mi_row + mi_dr , mi_col + mi_dc , subsize ) ;
 }
 }
 }