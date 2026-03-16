static const uint8_t * decode_tiles_mt ( VP9Decoder * pbi , const uint8_t * data , const uint8_t * data_end ) {
 VP9_COMMON * const cm = & pbi -> common ;
 const VP9WorkerInterface * const winterface = vp9_get_worker_interface ( ) ;
 const uint8_t * bit_reader_end = NULL ;
 const int aligned_mi_cols = mi_cols_aligned_to_sb ( cm -> mi_cols ) ;
 const int tile_cols = 1 << cm -> log2_tile_cols ;
 const int tile_rows = 1 << cm -> log2_tile_rows ;
 const int num_workers = MIN ( pbi -> max_threads & ~ 1 , tile_cols ) ;
 TileBuffer tile_buffers [ 1 ] [ 1 << 6 ] ;
 int n ;
 int final_worker = - 1 ;
 assert ( tile_cols <= ( 1 << 6 ) ) ;
 assert ( tile_rows == 1 ) ;
 ( void ) tile_rows ;
 if ( pbi -> num_tile_workers == 0 ) {
 const int num_threads = pbi -> max_threads & ~ 1 ;
 int i ;
 CHECK_MEM_ERROR ( cm , pbi -> tile_workers , vpx_malloc ( num_threads * sizeof ( * pbi -> tile_workers ) ) ) ;
 for ( i = 0 ;
 i < num_threads ;
 ++ i ) {
 VP9Worker * const worker = & pbi -> tile_workers [ i ] ;
 ++ pbi -> num_tile_workers ;
 winterface -> init ( worker ) ;
 CHECK_MEM_ERROR ( cm , worker -> data1 , vpx_memalign ( 32 , sizeof ( TileWorkerData ) ) ) ;
 CHECK_MEM_ERROR ( cm , worker -> data2 , vpx_malloc ( sizeof ( TileInfo ) ) ) ;
 if ( i < num_threads - 1 && ! winterface -> reset ( worker ) ) {
 vpx_internal_error ( & cm -> error , VPX_CODEC_ERROR , "Tile decoder thread creation failed" ) ;
 }
 }
 }
 for ( n = 0 ;
 n < num_workers ;
 ++ n ) {
 pbi -> tile_workers [ n ] . hook = ( VP9WorkerHook ) tile_worker_hook ;
 }
 vpx_memset ( cm -> above_context , 0 , sizeof ( * cm -> above_context ) * MAX_MB_PLANE * 2 * aligned_mi_cols ) ;
 vpx_memset ( cm -> above_seg_context , 0 , sizeof ( * cm -> above_seg_context ) * aligned_mi_cols ) ;
 get_tile_buffers ( pbi , data , data_end , tile_cols , tile_rows , tile_buffers ) ;
 qsort ( tile_buffers [ 0 ] , tile_cols , sizeof ( tile_buffers [ 0 ] [ 0 ] ) , compare_tile_buffers ) ;
 {
 int group_start = 0 ;
 while ( group_start < tile_cols ) {
 const TileBuffer largest = tile_buffers [ 0 ] [ group_start ] ;
 const int group_end = MIN ( group_start + num_workers , tile_cols ) - 1 ;
 memmove ( tile_buffers [ 0 ] + group_start , tile_buffers [ 0 ] + group_start + 1 , ( group_end - group_start ) * sizeof ( tile_buffers [ 0 ] [ 0 ] ) ) ;
 tile_buffers [ 0 ] [ group_end ] = largest ;
 group_start = group_end + 1 ;
 }
 }
 n = 0 ;
 while ( n < tile_cols ) {
 int i ;
 for ( i = 0 ;
 i < num_workers && n < tile_cols ;
 ++ i ) {
 VP9Worker * const worker = & pbi -> tile_workers [ i ] ;
 TileWorkerData * const tile_data = ( TileWorkerData * ) worker -> data1 ;
 TileInfo * const tile = ( TileInfo * ) worker -> data2 ;
 TileBuffer * const buf = & tile_buffers [ 0 ] [ n ] ;
 tile_data -> cm = cm ;
 tile_data -> xd = pbi -> mb ;
 tile_data -> xd . corrupted = 0 ;
 vp9_tile_init ( tile , tile_data -> cm , 0 , buf -> col ) ;
 setup_token_decoder ( buf -> data , data_end , buf -> size , & cm -> error , & tile_data -> bit_reader , pbi -> decrypt_cb , pbi -> decrypt_state ) ;
 init_macroblockd ( cm , & tile_data -> xd ) ;
 vp9_zero ( tile_data -> xd . dqcoeff ) ;
 worker -> had_error = 0 ;
 if ( i == num_workers - 1 || n == tile_cols - 1 ) {
 winterface -> execute ( worker ) ;
 }
 else {
 winterface -> launch ( worker ) ;
 }
 if ( buf -> col == tile_cols - 1 ) {
 final_worker = i ;
 }
 ++ n ;
 }
 for ( ;
 i > 0 ;
 -- i ) {
 VP9Worker * const worker = & pbi -> tile_workers [ i - 1 ] ;
 pbi -> mb . corrupted |= ! winterface -> sync ( worker ) ;
 }
 if ( final_worker > - 1 ) {
 TileWorkerData * const tile_data = ( TileWorkerData * ) pbi -> tile_workers [ final_worker ] . data1 ;
 bit_reader_end = vp9_reader_find_end ( & tile_data -> bit_reader ) ;
 final_worker = - 1 ;
 }
 }
 return bit_reader_end ;
 }