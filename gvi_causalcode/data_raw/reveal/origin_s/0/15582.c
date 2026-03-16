void vp9_decoder_remove ( VP9Decoder * pbi ) {
 VP9_COMMON * const cm = & pbi -> common ;
 int i ;
 vp9_get_worker_interface ( ) -> end ( & pbi -> lf_worker ) ;
 vpx_free ( pbi -> lf_worker . data1 ) ;
 vpx_free ( pbi -> tile_data ) ;
 for ( i = 0 ;
 i < pbi -> num_tile_workers ;
 ++ i ) {
 VP9Worker * const worker = & pbi -> tile_workers [ i ] ;
 vp9_get_worker_interface ( ) -> end ( worker ) ;
 vpx_free ( worker -> data1 ) ;
 vpx_free ( worker -> data2 ) ;
 }
 vpx_free ( pbi -> tile_workers ) ;
 if ( pbi -> num_tile_workers > 0 ) {
 vp9_loop_filter_dealloc ( & pbi -> lf_row_sync ) ;
 }
 vp9_remove_common ( cm ) ;
 vpx_free ( pbi ) ;
 }