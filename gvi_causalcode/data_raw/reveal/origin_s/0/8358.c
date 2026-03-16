void vp9_filter_block_plane ( VP9_COMMON * const cm , struct macroblockd_plane * const plane , int mi_row , LOOP_FILTER_MASK * lfm ) {
 struct buf_2d * const dst = & plane -> dst ;
 uint8_t * const dst0 = dst -> buf ;
 int r , c ;
 if ( ! plane -> plane_type ) {
 uint64_t mask_16x16 = lfm -> left_y [ TX_16X16 ] ;
 uint64_t mask_8x8 = lfm -> left_y [ TX_8X8 ] ;
 uint64_t mask_4x4 = lfm -> left_y [ TX_4X4 ] ;
 uint64_t mask_4x4_int = lfm -> int_4x4_y ;
 for ( r = 0 ;
 r < MI_BLOCK_SIZE && mi_row + r < cm -> mi_rows ;
 r += 2 ) {
 unsigned int mask_16x16_l = mask_16x16 & 0xffff ;
 unsigned int mask_8x8_l = mask_8x8 & 0xffff ;
 unsigned int mask_4x4_l = mask_4x4 & 0xffff ;
 unsigned int mask_4x4_int_l = mask_4x4_int & 0xffff ;
 filter_selectively_vert_row2 ( plane -> plane_type , dst -> buf , dst -> stride , mask_16x16_l , mask_8x8_l , mask_4x4_l , mask_4x4_int_l , & cm -> lf_info , & lfm -> lfl_y [ r << 3 ] ) ;
 dst -> buf += 16 * dst -> stride ;
 mask_16x16 >>= 16 ;
 mask_8x8 >>= 16 ;
 mask_4x4 >>= 16 ;
 mask_4x4_int >>= 16 ;
 }
 dst -> buf = dst0 ;
 mask_16x16 = lfm -> above_y [ TX_16X16 ] ;
 mask_8x8 = lfm -> above_y [ TX_8X8 ] ;
 mask_4x4 = lfm -> above_y [ TX_4X4 ] ;
 mask_4x4_int = lfm -> int_4x4_y ;
 for ( r = 0 ;
 r < MI_BLOCK_SIZE && mi_row + r < cm -> mi_rows ;
 r ++ ) {
 unsigned int mask_16x16_r ;
 unsigned int mask_8x8_r ;
 unsigned int mask_4x4_r ;
 if ( mi_row + r == 0 ) {
 mask_16x16_r = 0 ;
 mask_8x8_r = 0 ;
 mask_4x4_r = 0 ;
 }
 else {
 mask_16x16_r = mask_16x16 & 0xff ;
 mask_8x8_r = mask_8x8 & 0xff ;
 mask_4x4_r = mask_4x4 & 0xff ;
 }
 filter_selectively_horiz ( dst -> buf , dst -> stride , mask_16x16_r , mask_8x8_r , mask_4x4_r , mask_4x4_int & 0xff , & cm -> lf_info , & lfm -> lfl_y [ r << 3 ] ) ;
 dst -> buf += 8 * dst -> stride ;
 mask_16x16 >>= 8 ;
 mask_8x8 >>= 8 ;
 mask_4x4 >>= 8 ;
 mask_4x4_int >>= 8 ;
 }
 }
 else {
 uint16_t mask_16x16 = lfm -> left_uv [ TX_16X16 ] ;
 uint16_t mask_8x8 = lfm -> left_uv [ TX_8X8 ] ;
 uint16_t mask_4x4 = lfm -> left_uv [ TX_4X4 ] ;
 uint16_t mask_4x4_int = lfm -> int_4x4_uv ;
 for ( r = 0 ;
 r < MI_BLOCK_SIZE && mi_row + r < cm -> mi_rows ;
 r += 4 ) {
 if ( plane -> plane_type == 1 ) {
 for ( c = 0 ;
 c < ( MI_BLOCK_SIZE >> 1 ) ;
 c ++ ) {
 lfm -> lfl_uv [ ( r << 1 ) + c ] = lfm -> lfl_y [ ( r << 3 ) + ( c << 1 ) ] ;
 lfm -> lfl_uv [ ( ( r + 2 ) << 1 ) + c ] = lfm -> lfl_y [ ( ( r + 2 ) << 3 ) + ( c << 1 ) ] ;
 }
 }
 {
 unsigned int mask_16x16_l = mask_16x16 & 0xff ;
 unsigned int mask_8x8_l = mask_8x8 & 0xff ;
 unsigned int mask_4x4_l = mask_4x4 & 0xff ;
 unsigned int mask_4x4_int_l = mask_4x4_int & 0xff ;
 filter_selectively_vert_row2 ( plane -> plane_type , dst -> buf , dst -> stride , mask_16x16_l , mask_8x8_l , mask_4x4_l , mask_4x4_int_l , & cm -> lf_info , & lfm -> lfl_uv [ r << 1 ] ) ;
 dst -> buf += 16 * dst -> stride ;
 mask_16x16 >>= 8 ;
 mask_8x8 >>= 8 ;
 mask_4x4 >>= 8 ;
 mask_4x4_int >>= 8 ;
 }
 }
 dst -> buf = dst0 ;
 mask_16x16 = lfm -> above_uv [ TX_16X16 ] ;
 mask_8x8 = lfm -> above_uv [ TX_8X8 ] ;
 mask_4x4 = lfm -> above_uv [ TX_4X4 ] ;
 mask_4x4_int = lfm -> int_4x4_uv ;
 for ( r = 0 ;
 r < MI_BLOCK_SIZE && mi_row + r < cm -> mi_rows ;
 r += 2 ) {
 const int skip_border_4x4_r = mi_row + r == cm -> mi_rows - 1 ;
 const unsigned int mask_4x4_int_r = skip_border_4x4_r ? : ( mask_4x4_int & 0xf ) ;
 unsigned int mask_16x16_r ;
 unsigned int mask_8x8_r ;
 unsigned int mask_4x4_r ;
 if ( mi_row + r == 0 ) {
 mask_16x16_r = 0 ;
 mask_8x8_r = 0 ;
 mask_4x4_r = 0 ;
 }
 else {
 mask_16x16_r = mask_16x16 & 0xf ;
 mask_8x8_r = mask_8x8 & 0xf ;
 mask_4x4_r = mask_4x4 & 0xf ;
 }
 filter_selectively_horiz ( dst -> buf , dst -> stride , mask_16x16_r , mask_8x8_r , mask_4x4_r , mask_4x4_int_r , & cm -> lf_info , & lfm -> lfl_uv [ r << 1 ] ) ;
 dst -> buf += 8 * dst -> stride ;
 mask_16x16 >>= 4 ;
 mask_8x8 >>= 4 ;
 mask_4x4 >>= 4 ;
 mask_4x4_int >>= 4 ;
 }
 }
 }