static void temporal_filter_iterate_c ( VP9_COMP * cpi , YV12_BUFFER_CONFIG * * frames , int frame_count , int alt_ref_index , int strength , struct scale_factors * scale ) {
 int byte ;
 int frame ;
 int mb_col , mb_row ;
 unsigned int filter_weight ;
 int mb_cols = cpi -> common . mb_cols ;
 int mb_rows = cpi -> common . mb_rows ;
 int mb_y_offset = 0 ;
 int mb_uv_offset = 0 ;
 DECLARE_ALIGNED_ARRAY ( 16 , unsigned int , accumulator , 16 * 16 * 3 ) ;
 DECLARE_ALIGNED_ARRAY ( 16 , uint16_t , count , 16 * 16 * 3 ) ;
 MACROBLOCKD * mbd = & cpi -> mb . e_mbd ;
 YV12_BUFFER_CONFIG * f = frames [ alt_ref_index ] ;
 uint8_t * dst1 , * dst2 ;
 DECLARE_ALIGNED_ARRAY ( 16 , uint8_t , predictor , 16 * 16 * 3 ) ;
 const int mb_uv_height = 16 >> mbd -> plane [ 1 ] . subsampling_y ;
 const int mb_uv_width = 16 >> mbd -> plane [ 1 ] . subsampling_x ;
 uint8_t * input_buffer [ MAX_MB_PLANE ] ;
 int i ;
 for ( i = 0 ;
 i < MAX_MB_PLANE ;
 i ++ ) input_buffer [ i ] = mbd -> plane [ i ] . pre [ 0 ] . buf ;
 for ( mb_row = 0 ;
 mb_row < mb_rows ;
 mb_row ++ ) {
 cpi -> mb . mv_row_min = - ( ( mb_row * 16 ) + ( 17 - 2 * VP9_INTERP_EXTEND ) ) ;
 cpi -> mb . mv_row_max = ( ( cpi -> common . mb_rows - 1 - mb_row ) * 16 ) + ( 17 - 2 * VP9_INTERP_EXTEND ) ;
 for ( mb_col = 0 ;
 mb_col < mb_cols ;
 mb_col ++ ) {
 int i , j , k ;
 int stride ;
 vpx_memset ( accumulator , 0 , 16 * 16 * 3 * sizeof ( accumulator [ 0 ] ) ) ;
 vpx_memset ( count , 0 , 16 * 16 * 3 * sizeof ( count [ 0 ] ) ) ;
 cpi -> mb . mv_col_min = - ( ( mb_col * 16 ) + ( 17 - 2 * VP9_INTERP_EXTEND ) ) ;
 cpi -> mb . mv_col_max = ( ( cpi -> common . mb_cols - 1 - mb_col ) * 16 ) + ( 17 - 2 * VP9_INTERP_EXTEND ) ;
 for ( frame = 0 ;
 frame < frame_count ;
 frame ++ ) {
 const int thresh_low = 10000 ;
 const int thresh_high = 20000 ;
 if ( frames [ frame ] == NULL ) continue ;
 mbd -> mi [ 0 ] -> bmi [ 0 ] . as_mv [ 0 ] . as_mv . row = 0 ;
 mbd -> mi [ 0 ] -> bmi [ 0 ] . as_mv [ 0 ] . as_mv . col = 0 ;
 if ( frame == alt_ref_index ) {
 filter_weight = 2 ;
 }
 else {
 int err = temporal_filter_find_matching_mb_c ( cpi , frames [ alt_ref_index ] -> y_buffer + mb_y_offset , frames [ frame ] -> y_buffer + mb_y_offset , frames [ frame ] -> y_stride ) ;
 filter_weight = err < thresh_low ? 2 : err < thresh_high ? 1 : 0 ;
 }
 if ( filter_weight != 0 ) {
 temporal_filter_predictors_mb_c ( mbd , frames [ frame ] -> y_buffer + mb_y_offset , frames [ frame ] -> u_buffer + mb_uv_offset , frames [ frame ] -> v_buffer + mb_uv_offset , frames [ frame ] -> y_stride , mb_uv_width , mb_uv_height , mbd -> mi [ 0 ] -> bmi [ 0 ] . as_mv [ 0 ] . as_mv . row , mbd -> mi [ 0 ] -> bmi [ 0 ] . as_mv [ 0 ] . as_mv . col , predictor , scale , mb_col * 16 , mb_row * 16 ) ;
 vp9_temporal_filter_apply ( f -> y_buffer + mb_y_offset , f -> y_stride , predictor , 16 , 16 , strength , filter_weight , accumulator , count ) ;
 vp9_temporal_filter_apply ( f -> u_buffer + mb_uv_offset , f -> uv_stride , predictor + 256 , mb_uv_width , mb_uv_height , strength , filter_weight , accumulator + 256 , count + 256 ) ;
 vp9_temporal_filter_apply ( f -> v_buffer + mb_uv_offset , f -> uv_stride , predictor + 512 , mb_uv_width , mb_uv_height , strength , filter_weight , accumulator + 512 , count + 512 ) ;
 }
 }
 dst1 = cpi -> alt_ref_buffer . y_buffer ;
 stride = cpi -> alt_ref_buffer . y_stride ;
 byte = mb_y_offset ;
 for ( i = 0 , k = 0 ;
 i < 16 ;
 i ++ ) {
 for ( j = 0 ;
 j < 16 ;
 j ++ , k ++ ) {
 unsigned int pval = accumulator [ k ] + ( count [ k ] >> 1 ) ;
 pval *= fixed_divide [ count [ k ] ] ;
 pval >>= 19 ;
 dst1 [ byte ] = ( uint8_t ) pval ;
 byte ++ ;
 }
 byte += stride - 16 ;
 }
 dst1 = cpi -> alt_ref_buffer . u_buffer ;
 dst2 = cpi -> alt_ref_buffer . v_buffer ;
 stride = cpi -> alt_ref_buffer . uv_stride ;
 byte = mb_uv_offset ;
 for ( i = 0 , k = 256 ;
 i < mb_uv_height ;
 i ++ ) {
 for ( j = 0 ;
 j < mb_uv_width ;
 j ++ , k ++ ) {
 int m = k + 256 ;
 unsigned int pval = accumulator [ k ] + ( count [ k ] >> 1 ) ;
 pval *= fixed_divide [ count [ k ] ] ;
 pval >>= 19 ;
 dst1 [ byte ] = ( uint8_t ) pval ;
 pval = accumulator [ m ] + ( count [ m ] >> 1 ) ;
 pval *= fixed_divide [ count [ m ] ] ;
 pval >>= 19 ;
 dst2 [ byte ] = ( uint8_t ) pval ;
 byte ++ ;
 }
 byte += stride - mb_uv_width ;
 }
 mb_y_offset += 16 ;
 mb_uv_offset += mb_uv_width ;
 }
 mb_y_offset += 16 * ( f -> y_stride - mb_cols ) ;
 mb_uv_offset += mb_uv_height * f -> uv_stride - mb_uv_width * mb_cols ;
 }
 for ( i = 0 ;
 i < MAX_MB_PLANE ;
 i ++ ) mbd -> plane [ i ] . pre [ 0 ] . buf = input_buffer [ i ] ;
 }