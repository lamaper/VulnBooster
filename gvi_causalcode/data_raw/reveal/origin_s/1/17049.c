void vp9_loop_filter_frame_mt ( YV12_BUFFER_CONFIG * frame , VP9Decoder * pbi , VP9_COMMON * cm , int frame_filter_level , int y_only ) {
 VP9LfSync * const lf_sync = & pbi -> lf_row_sync ;
 const VP9WorkerInterface * const winterface = vp9_get_worker_interface ( ) ;
 const int sb_rows = mi_cols_aligned_to_sb ( cm -> mi_rows ) >> MI_BLOCK_SIZE_LOG2 ;
 const int tile_cols = 1 << cm -> log2_tile_cols ;
 const int num_workers = MIN ( pbi -> max_threads & ~ 1 , tile_cols ) ;
 int i ;
 if ( ! lf_sync -> sync_range || cm -> last_height != cm -> height ) {
 vp9_loop_filter_dealloc ( lf_sync ) ;
 vp9_loop_filter_alloc ( cm , lf_sync , sb_rows , cm -> width ) ;
 }
 if ( ! frame_filter_level ) return ;
 vp9_loop_filter_frame_init ( cm , frame_filter_level ) ;
 vpx_memset ( lf_sync -> cur_sb_col , - 1 , sizeof ( * lf_sync -> cur_sb_col ) * sb_rows ) ;
 for ( i = 0 ;
 i < num_workers ;
 ++ i ) {
 VP9Worker * const worker = & pbi -> tile_workers [ i ] ;
 TileWorkerData * const tile_data = ( TileWorkerData * ) worker -> data1 ;
 LFWorkerData * const lf_data = & tile_data -> lfdata ;
 worker -> hook = ( VP9WorkerHook ) loop_filter_row_worker ;
 lf_data -> frame_buffer = frame ;
 lf_data -> cm = cm ;
 vp9_copy ( lf_data -> planes , pbi -> mb . plane ) ;
 lf_data -> start = i ;
 lf_data -> stop = sb_rows ;
 lf_data -> y_only = y_only ;
 lf_data -> lf_sync = lf_sync ;
 lf_data -> num_lf_workers = num_workers ;
 if ( i == num_workers - 1 ) {
 winterface -> execute ( worker ) ;
 }
 else {
 winterface -> launch ( worker ) ;
 }
 }
 for ( i = 0 ;
 i < num_workers ;
 ++ i ) {
 winterface -> sync ( & pbi -> tile_workers [ i ] ) ;
 }
 }