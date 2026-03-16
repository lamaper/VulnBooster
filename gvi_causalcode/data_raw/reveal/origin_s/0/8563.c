static void variance_neon_w8 ( const uint8_t * a , int a_stride , const uint8_t * b , int b_stride , int w , int h , unsigned int * sse , int * sum ) {
 int i , j ;
 int16x8_t v_sum = vdupq_n_s16 ( 0 ) ;
 int32x4_t v_sse_lo = vdupq_n_s32 ( 0 ) ;
 int32x4_t v_sse_hi = vdupq_n_s32 ( 0 ) ;
 for ( i = 0 ;
 i < h ;
 ++ i ) {
 for ( j = 0 ;
 j < w ;
 j += 8 ) {
 const uint8x8_t v_a = vld1_u8 ( & a [ j ] ) ;
 const uint8x8_t v_b = vld1_u8 ( & b [ j ] ) ;
 const uint16x8_t v_diff = vsubl_u8 ( v_a , v_b ) ;
 const int16x8_t sv_diff = vreinterpretq_s16_u16 ( v_diff ) ;
 v_sum = vaddq_s16 ( v_sum , sv_diff ) ;
 v_sse_lo = vmlal_s16 ( v_sse_lo , vget_low_s16 ( sv_diff ) , vget_low_s16 ( sv_diff ) ) ;
 v_sse_hi = vmlal_s16 ( v_sse_hi , vget_high_s16 ( sv_diff ) , vget_high_s16 ( sv_diff ) ) ;
 }
 a += a_stride ;
 b += b_stride ;
 }
 * sum = horizontal_add_s16x8 ( v_sum ) ;
 * sse = ( unsigned int ) horizontal_add_s32x4 ( vaddq_s32 ( v_sse_lo , v_sse_hi ) ) ;
 }