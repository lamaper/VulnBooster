static void build_masks ( const loop_filter_info_n * const lfi_n , const MODE_INFO * mi , const int shift_y , const int shift_uv , LOOP_FILTER_MASK * lfm ) {
 const MB_MODE_INFO * mbmi = & mi -> mbmi ;
 const BLOCK_SIZE block_size = mbmi -> sb_type ;
 const TX_SIZE tx_size_y = mbmi -> tx_size ;
 const TX_SIZE tx_size_uv = get_uv_tx_size_impl ( tx_size_y , block_size , 1 , 1 ) ;
 const int filter_level = get_filter_level ( lfi_n , mbmi ) ;
 uint64_t * const left_y = & lfm -> left_y [ tx_size_y ] ;
 uint64_t * const above_y = & lfm -> above_y [ tx_size_y ] ;
 uint64_t * const int_4x4_y = & lfm -> int_4x4_y ;
 uint16_t * const left_uv = & lfm -> left_uv [ tx_size_uv ] ;
 uint16_t * const above_uv = & lfm -> above_uv [ tx_size_uv ] ;
 uint16_t * const int_4x4_uv = & lfm -> int_4x4_uv ;
 int i ;
 if ( ! filter_level ) {
 return ;
 }
 else {
 const int w = num_8x8_blocks_wide_lookup [ block_size ] ;
 const int h = num_8x8_blocks_high_lookup [ block_size ] ;
 int index = shift_y ;
 for ( i = 0 ;
 i < h ;
 i ++ ) {
 vpx_memset ( & lfm -> lfl_y [ index ] , filter_level , w ) ;
 index += 8 ;
 }
 }
 * above_y |= above_prediction_mask [ block_size ] << shift_y ;
 * above_uv |= above_prediction_mask_uv [ block_size ] << shift_uv ;
 * left_y |= left_prediction_mask [ block_size ] << shift_y ;
 * left_uv |= left_prediction_mask_uv [ block_size ] << shift_uv ;
 if ( mbmi -> skip && is_inter_block ( mbmi ) ) return ;
 * above_y |= ( size_mask [ block_size ] & above_64x64_txform_mask [ tx_size_y ] ) << shift_y ;
 * above_uv |= ( size_mask_uv [ block_size ] & above_64x64_txform_mask_uv [ tx_size_uv ] ) << shift_uv ;
 * left_y |= ( size_mask [ block_size ] & left_64x64_txform_mask [ tx_size_y ] ) << shift_y ;
 * left_uv |= ( size_mask_uv [ block_size ] & left_64x64_txform_mask_uv [ tx_size_uv ] ) << shift_uv ;
 if ( tx_size_y == TX_4X4 ) * int_4x4_y |= ( size_mask [ block_size ] & 0xffffffffffffffff ) << shift_y ;
 if ( tx_size_uv == TX_4X4 ) * int_4x4_uv |= ( size_mask_uv [ block_size ] & 0xffff ) << shift_uv ;
 }