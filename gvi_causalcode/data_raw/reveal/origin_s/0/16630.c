static void build_intra_predictors ( const MACROBLOCKD * xd , const uint8_t * ref , int ref_stride , uint8_t * dst , int dst_stride , PREDICTION_MODE mode , TX_SIZE tx_size , int up_available , int left_available , int right_available , int x , int y , int plane ) {
 int i ;
 DECLARE_ALIGNED_ARRAY ( 16 , uint8_t , left_col , 64 ) ;
 DECLARE_ALIGNED_ARRAY ( 16 , uint8_t , above_data , 128 + 16 ) ;
 uint8_t * above_row = above_data + 16 ;
 const uint8_t * const_above_row = above_row ;
 const int bs = 4 << tx_size ;
 int frame_width , frame_height ;
 int x0 , y0 ;
 const struct macroblockd_plane * const pd = & xd -> plane [ plane ] ;
 if ( plane == 0 ) {
 frame_width = xd -> cur_buf -> y_width ;
 frame_height = xd -> cur_buf -> y_height ;
 }
 else {
 frame_width = xd -> cur_buf -> uv_width ;
 frame_height = xd -> cur_buf -> uv_height ;
 }
 x0 = ( - xd -> mb_to_left_edge >> ( 3 + pd -> subsampling_x ) ) + x ;
 y0 = ( - xd -> mb_to_top_edge >> ( 3 + pd -> subsampling_y ) ) + y ;
 vpx_memset ( left_col , 129 , 64 ) ;
 if ( left_available ) {
 if ( xd -> mb_to_bottom_edge < 0 ) {
 if ( y0 + bs <= frame_height ) {
 for ( i = 0 ;
 i < bs ;
 ++ i ) left_col [ i ] = ref [ i * ref_stride - 1 ] ;
 }
 else {
 const int extend_bottom = frame_height - y0 ;
 for ( i = 0 ;
 i < extend_bottom ;
 ++ i ) left_col [ i ] = ref [ i * ref_stride - 1 ] ;
 for ( ;
 i < bs ;
 ++ i ) left_col [ i ] = ref [ ( extend_bottom - 1 ) * ref_stride - 1 ] ;
 }
 }
 else {
 for ( i = 0 ;
 i < bs ;
 ++ i ) left_col [ i ] = ref [ i * ref_stride - 1 ] ;
 }
 }
 if ( up_available ) {
 const uint8_t * above_ref = ref - ref_stride ;
 if ( xd -> mb_to_right_edge < 0 ) {
 if ( x0 + 2 * bs <= frame_width ) {
 if ( right_available && bs == 4 ) {
 vpx_memcpy ( above_row , above_ref , 2 * bs ) ;
 }
 else {
 vpx_memcpy ( above_row , above_ref , bs ) ;
 vpx_memset ( above_row + bs , above_row [ bs - 1 ] , bs ) ;
 }
 }
 else if ( x0 + bs <= frame_width ) {
 const int r = frame_width - x0 ;
 if ( right_available && bs == 4 ) {
 vpx_memcpy ( above_row , above_ref , r ) ;
 vpx_memset ( above_row + r , above_row [ r - 1 ] , x0 + 2 * bs - frame_width ) ;
 }
 else {
 vpx_memcpy ( above_row , above_ref , bs ) ;
 vpx_memset ( above_row + bs , above_row [ bs - 1 ] , bs ) ;
 }
 }
 else if ( x0 <= frame_width ) {
 const int r = frame_width - x0 ;
 if ( right_available && bs == 4 ) {
 vpx_memcpy ( above_row , above_ref , r ) ;
 vpx_memset ( above_row + r , above_row [ r - 1 ] , x0 + 2 * bs - frame_width ) ;
 }
 else {
 vpx_memcpy ( above_row , above_ref , r ) ;
 vpx_memset ( above_row + r , above_row [ r - 1 ] , x0 + 2 * bs - frame_width ) ;
 }
 }
 above_row [ - 1 ] = left_available ? above_ref [ - 1 ] : 129 ;
 }
 else {
 if ( bs == 4 && right_available && left_available ) {
 const_above_row = above_ref ;
 }
 else {
 vpx_memcpy ( above_row , above_ref , bs ) ;
 if ( bs == 4 && right_available ) vpx_memcpy ( above_row + bs , above_ref + bs , bs ) ;
 else vpx_memset ( above_row + bs , above_row [ bs - 1 ] , bs ) ;
 above_row [ - 1 ] = left_available ? above_ref [ - 1 ] : 129 ;
 }
 }
 }
 else {
 vpx_memset ( above_row , 127 , bs * 2 ) ;
 above_row [ - 1 ] = 127 ;
 }
 if ( mode == DC_PRED ) {
 dc_pred [ left_available ] [ up_available ] [ tx_size ] ( dst , dst_stride , const_above_row , left_col ) ;
 }
 else {
 pred [ mode ] [ tx_size ] ( dst , dst_stride , const_above_row , left_col ) ;
 }
 }