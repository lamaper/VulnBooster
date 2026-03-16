static void lsp_interpolate ( int16_t * lpc , int16_t * cur_lsp , int16_t * prev_lsp ) {
 int i ;
 int16_t * lpc_ptr = lpc ;
 ff_acelp_weighted_vector_sum ( lpc , cur_lsp , prev_lsp , 4096 , 12288 , 1 << 13 , 14 , LPC_ORDER ) ;
 ff_acelp_weighted_vector_sum ( lpc + LPC_ORDER , cur_lsp , prev_lsp , 8192 , 8192 , 1 << 13 , 14 , LPC_ORDER ) ;
 ff_acelp_weighted_vector_sum ( lpc + 2 * LPC_ORDER , cur_lsp , prev_lsp , 12288 , 4096 , 1 << 13 , 14 , LPC_ORDER ) ;
 memcpy ( lpc + 3 * LPC_ORDER , cur_lsp , LPC_ORDER * sizeof ( * lpc ) ) ;
 for ( i = 0 ;
 i < SUBFRAMES ;
 i ++ ) {
 lsp2lpc ( lpc_ptr ) ;
 lpc_ptr += LPC_ORDER ;
 }
 }