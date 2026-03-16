static const uint8_t * decode_tiles ( VP9Decoder * pbi , const uint8_t * data , const uint8_t * data_end ) {
 VP9_COMMON * const cm = & pbi -> common ;
 const VP9WorkerInterface * const winterface = vp9_get_worker_interface ( ) ;
 const int aligned_cols = mi_cols_aligned_to_sb ( cm -> mi_cols ) ;
 const int tile_cols = 1 << cm -> log2_tile_cols ;
 const int tile_rows = 1 << cm -> log2_tile_rows ;
 TileBuffer tile_buffers [ 4 ] [ 1 << 6 ] ;
 int tile_row , tile_col ;
 int mi_row , mi_col ;
 TileData * tile_data = NULL ;
 if ( cm -> lf . filter_level && pbi -> lf_worker . data1 == NULL ) {
 CHECK_MEM_ERROR ( cm , pbi -> lf_worker . data1 , vpx_memalign ( 32 , sizeof ( LFWorkerData ) ) ) ;
 pbi -> lf_worker . hook = ( VP9WorkerHook ) vp9_loop_filter_worker ;
 if ( pbi -> max_threads > 1 && ! winterface -> reset ( & pbi -> lf_worker ) ) {
 vpx_internal_error ( & cm -> error , VPX_CODEC_ERROR , "Loop filter thread creation failed" ) ;
 }
 }
 if ( cm -> lf . filter_level ) {
 LFWorkerData * const lf_data = ( LFWorkerData * ) pbi -> lf_worker . data1 ;
 lf_data -> frame_buffer = get_frame_new_buffer ( cm ) ;
 lf_data -> cm = cm ;
 vp9_copy ( lf_data -> planes , pbi -> mb . plane ) ;
 lf_data -> stop = 0 ;
 lf_data -> y_only = 0 ;
 vp9_loop_filter_frame_init ( cm , cm -> lf . filter_level ) ;
 }
 assert ( tile_rows <= 4 ) ;
 assert ( tile_cols <= ( 1 << 6 ) ) ;
 vpx_memset ( cm -> above_context , 0 , sizeof ( * cm -> above_context ) * MAX_MB_PLANE * 2 * aligned_cols ) ;
 vpx_memset ( cm -> above_seg_context , 0 , sizeof ( * cm -> above_seg_context ) * aligned_cols ) ;
 get_tile_buffers ( pbi , data , data_end , tile_cols , tile_rows , tile_buffers ) ;
 if ( pbi -> tile_data == NULL || ( tile_cols * tile_rows ) != pbi -> total_tiles ) {
 vpx_free ( pbi -> tile_data ) ;
 CHECK_MEM_ERROR ( cm , pbi -> tile_data , vpx_memalign ( 32 , tile_cols * tile_rows * ( sizeof ( * pbi -> tile_data ) ) ) ) ;
 pbi -> total_tiles = tile_rows * tile_cols ;
 }
 for ( tile_row = 0 ;
 tile_row < tile_rows ;
 ++ tile_row ) {
 for ( tile_col = 0 ;
 tile_col < tile_cols ;
 ++ tile_col ) {
 TileInfo tile ;
 const TileBuffer * const buf = & tile_buffers [ tile_row ] [ tile_col ] ;
 tile_data = pbi -> tile_data + tile_cols * tile_row + tile_col ;
 tile_data -> cm = cm ;
 tile_data -> xd = pbi -> mb ;
 tile_data -> xd . corrupted = 0 ;
 vp9_tile_init ( & tile , tile_data -> cm , tile_row , tile_col ) ;
 setup_token_decoder ( buf -> data , data_end , buf -> size , & cm -> error , & tile_data -> bit_reader , pbi -> decrypt_cb , pbi -> decrypt_state ) ;
 init_macroblockd ( cm , & tile_data -> xd ) ;
 vp9_zero ( tile_data -> xd . dqcoeff ) ;
 }
 }
 for ( tile_row = 0 ;
 tile_row < tile_rows ;
 ++ tile_row ) {
 TileInfo tile ;
 vp9_tile_set_row ( & tile , cm , tile_row ) ;
 for ( mi_row = tile . mi_row_start ;
 mi_row < tile . mi_row_end ;
 mi_row += MI_BLOCK_SIZE ) {
 for ( tile_col = 0 ;
 tile_col < tile_cols ;
 ++ tile_col ) {
 const int col = pbi -> inv_tile_order ? tile_cols - tile_col - 1 : tile_col ;
 tile_data = pbi -> tile_data + tile_cols * tile_row + col ;
 vp9_tile_set_col ( & tile , tile_data -> cm , col ) ;
 vp9_zero ( tile_data -> xd . left_context ) ;
 vp9_zero ( tile_data -> xd . left_seg_context ) ;
 for ( mi_col = tile . mi_col_start ;
 mi_col < tile . mi_col_end ;
 mi_col += MI_BLOCK_SIZE ) {
 decode_partition ( tile_data -> cm , & tile_data -> xd , & tile , mi_row , mi_col , & tile_data -> bit_reader , BLOCK_64X64 ) ;
 }
 pbi -> mb . corrupted |= tile_data -> xd . corrupted ;
 }
 if ( cm -> lf . filter_level ) {
 const int lf_start = mi_row - MI_BLOCK_SIZE ;
 LFWorkerData * const lf_data = ( LFWorkerData * ) pbi -> lf_worker . data1 ;
 if ( lf_start < 0 ) continue ;
 if ( mi_row + MI_BLOCK_SIZE >= cm -> mi_rows ) continue ;
 winterface -> sync ( & pbi -> lf_worker ) ;
 lf_data -> start = lf_start ;
 lf_data -> stop = mi_row ;
 if ( pbi -> max_threads > 1 ) {
 winterface -> launch ( & pbi -> lf_worker ) ;
 }
 else {
 winterface -> execute ( & pbi -> lf_worker ) ;
 }
 }
 }
 }
 if ( cm -> lf . filter_level ) {
 LFWorkerData * const lf_data = ( LFWorkerData * ) pbi -> lf_worker . data1 ;
 winterface -> sync ( & pbi -> lf_worker ) ;
 lf_data -> start = lf_data -> stop ;
 lf_data -> stop = cm -> mi_rows ;
 winterface -> execute ( & pbi -> lf_worker ) ;
 }
 tile_data = pbi -> tile_data + tile_cols * tile_rows - 1 ;
 return vp9_reader_find_end ( & tile_data -> bit_reader ) ;
 }