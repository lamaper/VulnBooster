static void reset_skip_tx_size ( VP9_COMMON * cm , TX_SIZE max_tx_size ) {
 int mi_row , mi_col ;
 const int mis = cm -> mi_stride ;
 MODE_INFO * * mi_ptr = cm -> mi_grid_visible ;
 for ( mi_row = 0 ;
 mi_row < cm -> mi_rows ;
 ++ mi_row , mi_ptr += mis ) {
 for ( mi_col = 0 ;
 mi_col < cm -> mi_cols ;
 ++ mi_col ) {
 if ( mi_ptr [ mi_col ] -> mbmi . tx_size > max_tx_size ) mi_ptr [ mi_col ] -> mbmi . tx_size = max_tx_size ;
 }
 }
 }