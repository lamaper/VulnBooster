static void filter_block_plane_non420 ( VP9_COMMON * cm , struct macroblockd_plane * plane , MODE_INFO * * mi_8x8 , int mi_row , int mi_col ) {
 const int ss_x = plane -> subsampling_x ;
 const int ss_y = plane -> subsampling_y ;
 const int row_step = 1 << ss_x ;
 const int col_step = 1 << ss_y ;
 const int row_step_stride = cm -> mi_stride * row_step ;
 struct buf_2d * const dst = & plane -> dst ;
 uint8_t * const dst0 = dst -> buf ;
 unsigned int mask_16x16 [ MI_BLOCK_SIZE ] = {
 0 }
 ;
 unsigned int mask_8x8 [ MI_BLOCK_SIZE ] = {
 0 }
 ;
 unsigned int mask_4x4 [ MI_BLOCK_SIZE ] = {
 0 }
 ;
 unsigned int mask_4x4_int [ MI_BLOCK_SIZE ] = {
 0 }
 ;
 uint8_t lfl [ MI_BLOCK_SIZE * MI_BLOCK_SIZE ] ;
 int r , c ;
 for ( r = 0 ;
 r < MI_BLOCK_SIZE && mi_row + r < cm -> mi_rows ;
 r += row_step ) {
 unsigned int mask_16x16_c = 0 ;
 unsigned int mask_8x8_c = 0 ;
 unsigned int mask_4x4_c = 0 ;
 unsigned int border_mask ;
 for ( c = 0 ;
 c < MI_BLOCK_SIZE && mi_col + c < cm -> mi_cols ;
 c += col_step ) {
 const MODE_INFO * mi = mi_8x8 [ c ] ;
 const BLOCK_SIZE sb_type = mi [ 0 ] . mbmi . sb_type ;
 const int skip_this = mi [ 0 ] . mbmi . skip && is_inter_block ( & mi [ 0 ] . mbmi ) ;
 const int block_edge_left = ( num_4x4_blocks_wide_lookup [ sb_type ] > 1 ) ? ! ( c & ( num_8x8_blocks_wide_lookup [ sb_type ] - 1 ) ) : 1 ;
 const int skip_this_c = skip_this && ! block_edge_left ;
 const int block_edge_above = ( num_4x4_blocks_high_lookup [ sb_type ] > 1 ) ? ! ( r & ( num_8x8_blocks_high_lookup [ sb_type ] - 1 ) ) : 1 ;
 const int skip_this_r = skip_this && ! block_edge_above ;
 const TX_SIZE tx_size = ( plane -> plane_type == PLANE_TYPE_UV ) ? get_uv_tx_size ( & mi [ 0 ] . mbmi , plane ) : mi [ 0 ] . mbmi . tx_size ;
 const int skip_border_4x4_c = ss_x && mi_col + c == cm -> mi_cols - 1 ;
 const int skip_border_4x4_r = ss_y && mi_row + r == cm -> mi_rows - 1 ;
 if ( ! ( lfl [ ( r << 3 ) + ( c >> ss_x ) ] = get_filter_level ( & cm -> lf_info , & mi [ 0 ] . mbmi ) ) ) continue ;
 if ( tx_size == TX_32X32 ) {
 if ( ! skip_this_c && ( ( c >> ss_x ) & 3 ) == 0 ) {
 if ( ! skip_border_4x4_c ) mask_16x16_c |= 1 << ( c >> ss_x ) ;
 else mask_8x8_c |= 1 << ( c >> ss_x ) ;
 }
 if ( ! skip_this_r && ( ( r >> ss_y ) & 3 ) == 0 ) {
 if ( ! skip_border_4x4_r ) mask_16x16 [ r ] |= 1 << ( c >> ss_x ) ;
 else mask_8x8 [ r ] |= 1 << ( c >> ss_x ) ;
 }
 }
 else if ( tx_size == TX_16X16 ) {
 if ( ! skip_this_c && ( ( c >> ss_x ) & 1 ) == 0 ) {
 if ( ! skip_border_4x4_c ) mask_16x16_c |= 1 << ( c >> ss_x ) ;
 else mask_8x8_c |= 1 << ( c >> ss_x ) ;
 }
 if ( ! skip_this_r && ( ( r >> ss_y ) & 1 ) == 0 ) {
 if ( ! skip_border_4x4_r ) mask_16x16 [ r ] |= 1 << ( c >> ss_x ) ;
 else mask_8x8 [ r ] |= 1 << ( c >> ss_x ) ;
 }
 }
 else {
 if ( ! skip_this_c ) {
 if ( tx_size == TX_8X8 || ( ( c >> ss_x ) & 3 ) == 0 ) mask_8x8_c |= 1 << ( c >> ss_x ) ;
 else mask_4x4_c |= 1 << ( c >> ss_x ) ;
 }
 if ( ! skip_this_r ) {
 if ( tx_size == TX_8X8 || ( ( r >> ss_y ) & 3 ) == 0 ) mask_8x8 [ r ] |= 1 << ( c >> ss_x ) ;
 else mask_4x4 [ r ] |= 1 << ( c >> ss_x ) ;
 }
 if ( ! skip_this && tx_size < TX_8X8 && ! skip_border_4x4_c ) mask_4x4_int [ r ] |= 1 << ( c >> ss_x ) ;
 }
 }
 border_mask = ~ ( mi_col == 0 ) ;
 filter_selectively_vert ( dst -> buf , dst -> stride , mask_16x16_c & border_mask , mask_8x8_c & border_mask , mask_4x4_c & border_mask , mask_4x4_int [ r ] , & cm -> lf_info , & lfl [ r << 3 ] ) ;
 dst -> buf += 8 * dst -> stride ;
 mi_8x8 += row_step_stride ;
 }
 dst -> buf = dst0 ;
 for ( r = 0 ;
 r < MI_BLOCK_SIZE && mi_row + r < cm -> mi_rows ;
 r += row_step ) {
 const int skip_border_4x4_r = ss_y && mi_row + r == cm -> mi_rows - 1 ;
 const unsigned int mask_4x4_int_r = skip_border_4x4_r ? 0 : mask_4x4_int [ r ] ;
 unsigned int mask_16x16_r ;
 unsigned int mask_8x8_r ;
 unsigned int mask_4x4_r ;
 if ( mi_row + r == 0 ) {
 mask_16x16_r = 0 ;
 mask_8x8_r = 0 ;
 mask_4x4_r = 0 ;
 }
 else {
 mask_16x16_r = mask_16x16 [ r ] ;
 mask_8x8_r = mask_8x8 [ r ] ;
 mask_4x4_r = mask_4x4 [ r ] ;
 }
 filter_selectively_horiz ( dst -> buf , dst -> stride , mask_16x16_r , mask_8x8_r , mask_4x4_r , mask_4x4_int_r , & cm -> lf_info , & lfl [ r << 3 ] ) ;
 dst -> buf += 8 * dst -> stride ;
 }
 }