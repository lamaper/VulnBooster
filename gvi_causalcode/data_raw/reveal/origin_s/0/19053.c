void vp9_setup_mask ( VP9_COMMON * const cm , const int mi_row , const int mi_col , MODE_INFO * mi , const int mode_info_stride , LOOP_FILTER_MASK * lfm ) {
 int idx_32 , idx_16 , idx_8 ;
 const loop_filter_info_n * const lfi_n = & cm -> lf_info ;
 MODE_INFO * mip = mi ;
 MODE_INFO * mip2 = mi ;
 const int offset_32 [ ] = {
 4 , ( mode_info_stride << 2 ) - 4 , 4 , - ( mode_info_stride << 2 ) - 4 }
 ;
 const int offset_16 [ ] = {
 2 , ( mode_info_stride << 1 ) - 2 , 2 , - ( mode_info_stride << 1 ) - 2 }
 ;
 const int offset [ ] = {
 1 , mode_info_stride - 1 , 1 , - mode_info_stride - 1 }
 ;
 const int shift_32_y [ ] = {
 0 , 4 , 32 , 36 }
 ;
 const int shift_16_y [ ] = {
 0 , 2 , 16 , 18 }
 ;
 const int shift_8_y [ ] = {
 0 , 1 , 8 , 9 }
 ;
 const int shift_32_uv [ ] = {
 0 , 2 , 8 , 10 }
 ;
 const int shift_16_uv [ ] = {
 0 , 1 , 4 , 5 }
 ;
 int i ;
 const int max_rows = ( mi_row + MI_BLOCK_SIZE > cm -> mi_rows ? cm -> mi_rows - mi_row : MI_BLOCK_SIZE ) ;
 const int max_cols = ( mi_col + MI_BLOCK_SIZE > cm -> mi_cols ? cm -> mi_cols - mi_col : MI_BLOCK_SIZE ) ;
 vp9_zero ( * lfm ) ;
 assert ( mip != NULL ) ;
 switch ( mip -> mbmi . sb_type ) {
 case BLOCK_64X64 : build_masks ( lfi_n , mip , 0 , 0 , lfm ) ;
 break ;
 case BLOCK_64X32 : build_masks ( lfi_n , mip , 0 , 0 , lfm ) ;
 mip2 = mip + mode_info_stride * 4 ;
 if ( 4 >= max_rows ) break ;
 build_masks ( lfi_n , mip2 , 32 , 8 , lfm ) ;
 break ;
 case BLOCK_32X64 : build_masks ( lfi_n , mip , 0 , 0 , lfm ) ;
 mip2 = mip + 4 ;
 if ( 4 >= max_cols ) break ;
 build_masks ( lfi_n , mip2 , 4 , 2 , lfm ) ;
 break ;
 default : for ( idx_32 = 0 ;
 idx_32 < 4 ;
 mip += offset_32 [ idx_32 ] , ++ idx_32 ) {
 const int shift_y = shift_32_y [ idx_32 ] ;
 const int shift_uv = shift_32_uv [ idx_32 ] ;
 const int mi_32_col_offset = ( ( idx_32 & 1 ) << 2 ) ;
 const int mi_32_row_offset = ( ( idx_32 >> 1 ) << 2 ) ;
 if ( mi_32_col_offset >= max_cols || mi_32_row_offset >= max_rows ) continue ;
 switch ( mip -> mbmi . sb_type ) {
 case BLOCK_32X32 : build_masks ( lfi_n , mip , shift_y , shift_uv , lfm ) ;
 break ;
 case BLOCK_32X16 : build_masks ( lfi_n , mip , shift_y , shift_uv , lfm ) ;
 if ( mi_32_row_offset + 2 >= max_rows ) continue ;
 mip2 = mip + mode_info_stride * 2 ;
 build_masks ( lfi_n , mip2 , shift_y + 16 , shift_uv + 4 , lfm ) ;
 break ;
 case BLOCK_16X32 : build_masks ( lfi_n , mip , shift_y , shift_uv , lfm ) ;
 if ( mi_32_col_offset + 2 >= max_cols ) continue ;
 mip2 = mip + 2 ;
 build_masks ( lfi_n , mip2 , shift_y + 2 , shift_uv + 1 , lfm ) ;
 break ;
 default : for ( idx_16 = 0 ;
 idx_16 < 4 ;
 mip += offset_16 [ idx_16 ] , ++ idx_16 ) {
 const int shift_y = shift_32_y [ idx_32 ] + shift_16_y [ idx_16 ] ;
 const int shift_uv = shift_32_uv [ idx_32 ] + shift_16_uv [ idx_16 ] ;
 const int mi_16_col_offset = mi_32_col_offset + ( ( idx_16 & 1 ) << 1 ) ;
 const int mi_16_row_offset = mi_32_row_offset + ( ( idx_16 >> 1 ) << 1 ) ;
 if ( mi_16_col_offset >= max_cols || mi_16_row_offset >= max_rows ) continue ;
 switch ( mip -> mbmi . sb_type ) {
 case BLOCK_16X16 : build_masks ( lfi_n , mip , shift_y , shift_uv , lfm ) ;
 break ;
 case BLOCK_16X8 : build_masks ( lfi_n , mip , shift_y , shift_uv , lfm ) ;
 if ( mi_16_row_offset + 1 >= max_rows ) continue ;
 mip2 = mip + mode_info_stride ;
 build_y_mask ( lfi_n , mip2 , shift_y + 8 , lfm ) ;
 break ;
 case BLOCK_8X16 : build_masks ( lfi_n , mip , shift_y , shift_uv , lfm ) ;
 if ( mi_16_col_offset + 1 >= max_cols ) continue ;
 mip2 = mip + 1 ;
 build_y_mask ( lfi_n , mip2 , shift_y + 1 , lfm ) ;
 break ;
 default : {
 const int shift_y = shift_32_y [ idx_32 ] + shift_16_y [ idx_16 ] + shift_8_y [ 0 ] ;
 build_masks ( lfi_n , mip , shift_y , shift_uv , lfm ) ;
 mip += offset [ 0 ] ;
 for ( idx_8 = 1 ;
 idx_8 < 4 ;
 mip += offset [ idx_8 ] , ++ idx_8 ) {
 const int shift_y = shift_32_y [ idx_32 ] + shift_16_y [ idx_16 ] + shift_8_y [ idx_8 ] ;
 const int mi_8_col_offset = mi_16_col_offset + ( ( idx_8 & 1 ) ) ;
 const int mi_8_row_offset = mi_16_row_offset + ( ( idx_8 >> 1 ) ) ;
 if ( mi_8_col_offset >= max_cols || mi_8_row_offset >= max_rows ) continue ;
 build_y_mask ( lfi_n , mip , shift_y , lfm ) ;
 }
 break ;
 }
 }
 }
 break ;
 }
 }
 break ;
 }
 lfm -> left_y [ TX_16X16 ] |= lfm -> left_y [ TX_32X32 ] ;
 lfm -> above_y [ TX_16X16 ] |= lfm -> above_y [ TX_32X32 ] ;
 lfm -> left_uv [ TX_16X16 ] |= lfm -> left_uv [ TX_32X32 ] ;
 lfm -> above_uv [ TX_16X16 ] |= lfm -> above_uv [ TX_32X32 ] ;
 lfm -> left_y [ TX_8X8 ] |= lfm -> left_y [ TX_4X4 ] & left_border ;
 lfm -> left_y [ TX_4X4 ] &= ~ left_border ;
 lfm -> above_y [ TX_8X8 ] |= lfm -> above_y [ TX_4X4 ] & above_border ;
 lfm -> above_y [ TX_4X4 ] &= ~ above_border ;
 lfm -> left_uv [ TX_8X8 ] |= lfm -> left_uv [ TX_4X4 ] & left_border_uv ;
 lfm -> left_uv [ TX_4X4 ] &= ~ left_border_uv ;
 lfm -> above_uv [ TX_8X8 ] |= lfm -> above_uv [ TX_4X4 ] & above_border_uv ;
 lfm -> above_uv [ TX_4X4 ] &= ~ above_border_uv ;
 if ( mi_row + MI_BLOCK_SIZE > cm -> mi_rows ) {
 const uint64_t rows = cm -> mi_rows - mi_row ;
 const uint64_t mask_y = ( ( ( uint64_t ) 1 << ( rows << 3 ) ) - 1 ) ;
 const uint16_t mask_uv = ( ( ( uint16_t ) 1 << ( ( ( rows + 1 ) >> 1 ) << 2 ) ) - 1 ) ;
 for ( i = 0 ;
 i < TX_32X32 ;
 i ++ ) {
 lfm -> left_y [ i ] &= mask_y ;
 lfm -> above_y [ i ] &= mask_y ;
 lfm -> left_uv [ i ] &= mask_uv ;
 lfm -> above_uv [ i ] &= mask_uv ;
 }
 lfm -> int_4x4_y &= mask_y ;
 lfm -> int_4x4_uv &= mask_uv ;
 if ( rows == 1 ) {
 lfm -> above_uv [ TX_8X8 ] |= lfm -> above_uv [ TX_16X16 ] ;
 lfm -> above_uv [ TX_16X16 ] = 0 ;
 }
 if ( rows == 5 ) {
 lfm -> above_uv [ TX_8X8 ] |= lfm -> above_uv [ TX_16X16 ] & 0xff00 ;
 lfm -> above_uv [ TX_16X16 ] &= ~ ( lfm -> above_uv [ TX_16X16 ] & 0xff00 ) ;
 }
 }
 if ( mi_col + MI_BLOCK_SIZE > cm -> mi_cols ) {
 const uint64_t columns = cm -> mi_cols - mi_col ;
 const uint64_t mask_y = ( ( ( 1 << columns ) - 1 ) ) * 0x0101010101010101 ;
 const uint16_t mask_uv = ( ( 1 << ( ( columns + 1 ) >> 1 ) ) - 1 ) * 0x1111 ;
 const uint16_t mask_uv_int = ( ( 1 << ( columns >> 1 ) ) - 1 ) * 0x1111 ;
 for ( i = 0 ;
 i < TX_32X32 ;
 i ++ ) {
 lfm -> left_y [ i ] &= mask_y ;
 lfm -> above_y [ i ] &= mask_y ;
 lfm -> left_uv [ i ] &= mask_uv ;
 lfm -> above_uv [ i ] &= mask_uv ;
 }
 lfm -> int_4x4_y &= mask_y ;
 lfm -> int_4x4_uv &= mask_uv_int ;
 if ( columns == 1 ) {
 lfm -> left_uv [ TX_8X8 ] |= lfm -> left_uv [ TX_16X16 ] ;
 lfm -> left_uv [ TX_16X16 ] = 0 ;
 }
 if ( columns == 5 ) {
 lfm -> left_uv [ TX_8X8 ] |= ( lfm -> left_uv [ TX_16X16 ] & 0xcccc ) ;
 lfm -> left_uv [ TX_16X16 ] &= ~ ( lfm -> left_uv [ TX_16X16 ] & 0xcccc ) ;
 }
 }
 if ( mi_col == 0 ) {
 for ( i = 0 ;
 i < TX_32X32 ;
 i ++ ) {
 lfm -> left_y [ i ] &= 0xfefefefefefefefe ;
 lfm -> left_uv [ i ] &= 0xeeee ;
 }
 }
 assert ( ! ( lfm -> left_y [ TX_16X16 ] & lfm -> left_y [ TX_8X8 ] ) ) ;
 assert ( ! ( lfm -> left_y [ TX_16X16 ] & lfm -> left_y [ TX_4X4 ] ) ) ;
 assert ( ! ( lfm -> left_y [ TX_8X8 ] & lfm -> left_y [ TX_4X4 ] ) ) ;
 assert ( ! ( lfm -> int_4x4_y & lfm -> left_y [ TX_16X16 ] ) ) ;
 assert ( ! ( lfm -> left_uv [ TX_16X16 ] & lfm -> left_uv [ TX_8X8 ] ) ) ;
 assert ( ! ( lfm -> left_uv [ TX_16X16 ] & lfm -> left_uv [ TX_4X4 ] ) ) ;
 assert ( ! ( lfm -> left_uv [ TX_8X8 ] & lfm -> left_uv [ TX_4X4 ] ) ) ;
 assert ( ! ( lfm -> int_4x4_uv & lfm -> left_uv [ TX_16X16 ] ) ) ;
 assert ( ! ( lfm -> above_y [ TX_16X16 ] & lfm -> above_y [ TX_8X8 ] ) ) ;
 assert ( ! ( lfm -> above_y [ TX_16X16 ] & lfm -> above_y [ TX_4X4 ] ) ) ;
 assert ( ! ( lfm -> above_y [ TX_8X8 ] & lfm -> above_y [ TX_4X4 ] ) ) ;
 assert ( ! ( lfm -> int_4x4_y & lfm -> above_y [ TX_16X16 ] ) ) ;
 assert ( ! ( lfm -> above_uv [ TX_16X16 ] & lfm -> above_uv [ TX_8X8 ] ) ) ;
 assert ( ! ( lfm -> above_uv [ TX_16X16 ] & lfm -> above_uv [ TX_4X4 ] ) ) ;
 assert ( ! ( lfm -> above_uv [ TX_8X8 ] & lfm -> above_uv [ TX_4X4 ] ) ) ;
 assert ( ! ( lfm -> int_4x4_uv & lfm -> above_uv [ TX_16X16 ] ) ) ;
 }