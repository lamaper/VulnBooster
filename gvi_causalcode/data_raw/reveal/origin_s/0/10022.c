void vp9_ ## type ## _predictor_ ## size ## x ## size ## _c ( uint8_t * dst , ptrdiff_t stride , const uint8_t * above , const uint8_t * left ) {
 type ## _predictor ( dst , stride , size , above , left ) ;
 }

 high_ ## type ## _predictor ( dst , stride , size , above , left , bd ) ;
 }

 int r , c ;
 ( void ) above ;
 ( void ) bd ;
 for ( r = 0 ;
 r < bs - 1 ;
 ++ r ) {
 dst [ r * stride ] = ROUND_POWER_OF_TWO ( left [ r ] + left [ r + 1 ] , 1 ) ;
 }
 dst [ ( bs - 1 ) * stride ] = left [ bs - 1 ] ;
 dst ++ ;
 for ( r = 0 ;
 r < bs - 2 ;
 ++ r ) {
 dst [ r * stride ] = ROUND_POWER_OF_TWO ( left [ r ] + left [ r + 1 ] * 2 + left [ r + 2 ] , 2 ) ;
 }
 dst [ ( bs - 2 ) * stride ] = ROUND_POWER_OF_TWO ( left [ bs - 2 ] + left [ bs - 1 ] * 3 , 2 ) ;
 dst [ ( bs - 1 ) * stride ] = left [ bs - 1 ] ;
 dst ++ ;
 for ( c = 0 ;
 c < bs - 2 ;
 ++ c ) dst [ ( bs - 1 ) * stride + c ] = left [ bs - 1 ] ;
 for ( r = bs - 2 ;
 r >= 0 ;
 -- r ) {
 for ( c = 0 ;
 c < bs - 2 ;
 ++ c ) dst [ r * stride + c ] = dst [ ( r + 1 ) * stride + c - 2 ] ;
 }
 }
 static INLINE void high_d63_predictor ( uint16_t * dst , ptrdiff_t stride , int bs , const uint16_t * above , const uint16_t * left , int bd ) {
 int r , c ;
 ( void ) left ;
 ( void ) bd ;
 for ( r = 0 ;
 r < bs ;
 ++ r ) {
 for ( c = 0 ;
 c < bs ;
 ++ c ) {
 dst [ c ] = r & 1 ? ROUND_POWER_OF_TWO ( above [ r / 2 + c ] + above [ r / 2 + c + 1 ] * 2 + above [ r / 2 + c + 2 ] , 2 ) : ROUND_POWER_OF_TWO ( above [ r / 2 + c ] + above [ r / 2 + c + 1 ] , 1 ) ;
 }
 dst += stride ;
 }
 }
 static INLINE void high_d45_predictor ( uint16_t * dst , ptrdiff_t stride , int bs , const uint16_t * above , const uint16_t * left , int bd ) {
 int r , c ;
 ( void ) left ;
 ( void ) bd ;
 for ( r = 0 ;
 r < bs ;
 ++ r ) {
 for ( c = 0 ;
 c < bs ;
 ++ c ) {
 dst [ c ] = r + c + 2 < bs * 2 ? ROUND_POWER_OF_TWO ( above [ r + c ] + above [ r + c + 1 ] * 2 + above [ r + c + 2 ] , 2 ) : above [ bs * 2 - 1 ] ;
 }
 dst += stride ;
 }
 }
 static INLINE void high_d117_predictor ( uint16_t * dst , ptrdiff_t stride , int bs , const uint16_t * above , const uint16_t * left , int bd ) {
 int r , c ;
 ( void ) bd ;
 for ( c = 0 ;
 c < bs ;
 c ++ ) dst [ c ] = ROUND_POWER_OF_TWO ( above [ c - 1 ] + above [ c ] , 1 ) ;
 dst += stride ;
 dst [ 0 ] = ROUND_POWER_OF_TWO ( left [ 0 ] + above [ - 1 ] * 2 + above [ 0 ] , 2 ) ;
 for ( c = 1 ;
 c < bs ;
 c ++ ) dst [ c ] = ROUND_POWER_OF_TWO ( above [ c - 2 ] + above [ c - 1 ] * 2 + above [ c ] , 2 ) ;
 dst += stride ;
 dst [ 0 ] = ROUND_POWER_OF_TWO ( above [ - 1 ] + left [ 0 ] * 2 + left [ 1 ] , 2 ) ;
 for ( r = 3 ;
 r < bs ;
 ++ r ) dst [ ( r - 2 ) * stride ] = ROUND_POWER_OF_TWO ( left [ r - 3 ] + left [ r - 2 ] * 2 + left [ r - 1 ] , 2 ) ;
 for ( r = 2 ;
 r < bs ;
 ++ r ) {
 for ( c = 1 ;
 c < bs ;
 c ++ ) dst [ c ] = dst [ - 2 * stride + c - 1 ] ;
 dst += stride ;
 }
 }
 static INLINE void high_d135_predictor ( uint16_t * dst , ptrdiff_t stride , int bs , const uint16_t * above , const uint16_t * left , int bd ) {
 int r , c ;
 ( void ) bd ;
 dst [ 0 ] = ROUND_POWER_OF_TWO ( left [ 0 ] + above [ - 1 ] * 2 + above [ 0 ] , 2 ) ;
 for ( c = 1 ;
 c < bs ;
 c ++ ) dst [ c ] = ROUND_POWER_OF_TWO ( above [ c - 2 ] + above [ c - 1 ] * 2 + above [ c ] , 2 ) ;
 dst [ stride ] = ROUND_POWER_OF_TWO ( above [ - 1 ] + left [ 0 ] * 2 + left [ 1 ] , 2 ) ;
 for ( r = 2 ;
 r < bs ;
 ++ r ) dst [ r * stride ] = ROUND_POWER_OF_TWO ( left [ r - 2 ] + left [ r - 1 ] * 2 + left [ r ] , 2 ) ;
 dst += stride ;
 for ( r = 1 ;
 r < bs ;
 ++ r ) {
 for ( c = 1 ;
 c < bs ;
 c ++ ) dst [ c ] = dst [ - stride + c - 1 ] ;
 dst += stride ;
 }
 }
 static INLINE void high_d153_predictor ( uint16_t * dst , ptrdiff_t stride , int bs , const uint16_t * above , const uint16_t * left , int bd ) {
 int r , c ;
 ( void ) bd ;
 dst [ 0 ] = ROUND_POWER_OF_TWO ( above [ - 1 ] + left [ 0 ] , 1 ) ;
 for ( r = 1 ;
 r < bs ;
 r ++ ) dst [ r * stride ] = ROUND_POWER_OF_TWO ( left [ r - 1 ] + left [ r ] , 1 ) ;
 dst ++ ;
 dst [ 0 ] = ROUND_POWER_OF_TWO ( left [ 0 ] + above [ - 1 ] * 2 + above [ 0 ] , 2 ) ;
 dst [ stride ] = ROUND_POWER_OF_TWO ( above [ - 1 ] + left [ 0 ] * 2 + left [ 1 ] , 2 ) ;
 for ( r = 2 ;
 r < bs ;
 r ++ ) dst [ r * stride ] = ROUND_POWER_OF_TWO ( left [ r - 2 ] + left [ r - 1 ] * 2 + left [ r ] , 2 ) ;
 dst ++ ;
 for ( c = 0 ;
 c < bs - 2 ;
 c ++ ) dst [ c ] = ROUND_POWER_OF_TWO ( above [ c - 1 ] + above [ c ] * 2 + above [ c + 1 ] , 2 ) ;
 dst += stride ;
 for ( r = 1 ;
 r < bs ;
 ++ r ) {
 for ( c = 0 ;
 c < bs - 2 ;
 c ++ ) dst [ c ] = dst [ - stride + c - 2 ] ;
 dst += stride ;
 }
 }
 static INLINE void high_v_predictor ( uint16_t * dst , ptrdiff_t stride , int bs , const uint16_t * above , const uint16_t * left , int bd ) {
 int r ;
 ( void ) left ;
 ( void ) bd ;
 for ( r = 0 ;
 r < bs ;
 r ++ ) {
 vpx_memcpy ( dst , above , bs * sizeof ( uint16_t ) ) ;
 dst += stride ;
 }
 }
 static INLINE void high_h_predictor ( uint16_t * dst , ptrdiff_t stride , int bs , const uint16_t * above , const uint16_t * left , int bd ) {
 int r ;
 ( void ) above ;
 ( void ) bd ;
 for ( r = 0 ;
 r < bs ;
 r ++ ) {
 vpx_memset16 ( dst , left [ r ] , bs ) ;
 dst += stride ;
 }
 }
 static INLINE void high_tm_predictor ( uint16_t * dst , ptrdiff_t stride , int bs , const uint16_t * above , const uint16_t * left , int bd ) {
 int r , c ;
 int ytop_left = above [ - 1 ] ;
 ( void ) bd ;
 for ( r = 0 ;
 r < bs ;
 r ++ ) {
 for ( c = 0 ;
 c < bs ;
 c ++ ) dst [ c ] = clip_pixel_high ( left [ r ] + above [ c ] - ytop_left , bd ) ;
 dst += stride ;
 }
 }
 static INLINE void high_dc_128_predictor ( uint16_t * dst , ptrdiff_t stride , int bs , const uint16_t * above , const uint16_t * left , int bd ) {
 int r ;
 ( void ) above ;
 ( void ) left ;
 for ( r = 0 ;
 r < bs ;
 r ++ ) {
 vpx_memset16 ( dst , 128 << ( bd - 8 ) , bs ) ;
 dst += stride ;
 }
 }
 static INLINE void high_dc_left_predictor ( uint16_t * dst , ptrdiff_t stride , int bs , const uint16_t * above , const uint16_t * left , int bd ) {
 int i , r , expected_dc , sum = 0 ;
 ( void ) above ;
 ( void ) bd ;
 for ( i = 0 ;
 i < bs ;
 i ++ ) sum += left [ i ] ;
 expected_dc = ( sum + ( bs >> 1 ) ) / bs ;
 for ( r = 0 ;
 r < bs ;
 r ++ ) {
 vpx_memset16 ( dst , expected_dc , bs ) ;
 dst += stride ;
 }
 }
 static INLINE void high_dc_top_predictor ( uint16_t * dst , ptrdiff_t stride , int bs , const uint16_t * above , const uint16_t * left , int bd ) {
 int i , r , expected_dc , sum = 0 ;
 ( void ) left ;
 ( void ) bd ;
 for ( i = 0 ;
 i < bs ;
 i ++ ) sum += above [ i ] ;
 expected_dc = ( sum + ( bs >> 1 ) ) / bs ;
 for ( r = 0 ;
 r < bs ;
 r ++ ) {
 vpx_memset16 ( dst , expected_dc , bs ) ;
 dst += stride ;
 }
 }
 static INLINE void high_dc_predictor ( uint16_t * dst , ptrdiff_t stride , int bs , const uint16_t * above , const uint16_t * left , int bd ) {
 int i , r , expected_dc , sum = 0 ;
 const int count = 2 * bs ;
 ( void ) bd ;
 for ( i = 0 ;
 i < bs ;
 i ++ ) {
 sum += above [ i ] ;
 sum += left [ i ] ;
 }
 expected_dc = ( sum + ( count >> 1 ) ) / count ;
 for ( r = 0 ;
 r < bs ;
 r ++ ) {
 vpx_memset16 ( dst , expected_dc , bs ) ;
 dst += stride ;
 }
 }

 int r , c ;
 ( void ) above ;
 for ( r = 0 ;
 r < bs - 1 ;
 ++ r ) dst [ r * stride ] = ROUND_POWER_OF_TWO ( left [ r ] + left [ r + 1 ] , 1 ) ;
 dst [ ( bs - 1 ) * stride ] = left [ bs - 1 ] ;
 dst ++ ;
 for ( r = 0 ;
 r < bs - 2 ;
 ++ r ) dst [ r * stride ] = ROUND_POWER_OF_TWO ( left [ r ] + left [ r + 1 ] * 2 + left [ r + 2 ] , 2 ) ;
 dst [ ( bs - 2 ) * stride ] = ROUND_POWER_OF_TWO ( left [ bs - 2 ] + left [ bs - 1 ] * 3 , 2 ) ;
 dst [ ( bs - 1 ) * stride ] = left [ bs - 1 ] ;
 dst ++ ;
 for ( c = 0 ;
 c < bs - 2 ;
 ++ c ) dst [ ( bs - 1 ) * stride + c ] = left [ bs - 1 ] ;
 for ( r = bs - 2 ;
 r >= 0 ;
 -- r ) for ( c = 0 ;
 c < bs - 2 ;
 ++ c ) dst [ r * stride + c ] = dst [ ( r + 1 ) * stride + c - 2 ] ;
 }
 intra_pred_allsizes ( d207 ) static INLINE void d63_predictor ( uint8_t * dst , ptrdiff_t stride , int bs , const uint8_t * above , const uint8_t * left ) {
 int r , c ;
 ( void ) left ;
 for ( r = 0 ;
 r < bs ;
 ++ r ) {
 for ( c = 0 ;
 c < bs ;
 ++ c ) dst [ c ] = r & 1 ? ROUND_POWER_OF_TWO ( above [ r / 2 + c ] + above [ r / 2 + c + 1 ] * 2 + above [ r / 2 + c + 2 ] , 2 ) : ROUND_POWER_OF_TWO ( above [ r / 2 + c ] + above [ r / 2 + c + 1 ] , 1 ) ;
 dst += stride ;
 }
 }
 intra_pred_allsizes ( d63 ) static INLINE void d45_predictor ( uint8_t * dst , ptrdiff_t stride , int bs , const uint8_t * above , const uint8_t * left ) {
 int r , c ;
 ( void ) left ;
 for ( r = 0 ;
 r < bs ;
 ++ r ) {
 for ( c = 0 ;
 c < bs ;
 ++ c ) dst [ c ] = r + c + 2 < bs * 2 ? ROUND_POWER_OF_TWO ( above [ r + c ] + above [ r + c + 1 ] * 2 + above [ r + c + 2 ] , 2 ) : above [ bs * 2 - 1 ] ;
 dst += stride ;
 }
 }
 intra_pred_allsizes ( d45 ) static INLINE void d117_predictor ( uint8_t * dst , ptrdiff_t stride , int bs , const uint8_t * above , const uint8_t * left ) {
 int r , c ;
 for ( c = 0 ;
 c < bs ;
 c ++ ) dst [ c ] = ROUND_POWER_OF_TWO ( above [ c - 1 ] + above [ c ] , 1 ) ;
 dst += stride ;
 dst [ 0 ] = ROUND_POWER_OF_TWO ( left [ 0 ] + above [ - 1 ] * 2 + above [ 0 ] , 2 ) ;
 for ( c = 1 ;
 c < bs ;
 c ++ ) dst [ c ] = ROUND_POWER_OF_TWO ( above [ c - 2 ] + above [ c - 1 ] * 2 + above [ c ] , 2 ) ;
 dst += stride ;
 dst [ 0 ] = ROUND_POWER_OF_TWO ( above [ - 1 ] + left [ 0 ] * 2 + left [ 1 ] , 2 ) ;
 for ( r = 3 ;
 r < bs ;
 ++ r ) dst [ ( r - 2 ) * stride ] = ROUND_POWER_OF_TWO ( left [ r - 3 ] + left [ r - 2 ] * 2 + left [ r - 1 ] , 2 ) ;
 for ( r = 2 ;
 r < bs ;
 ++ r ) {
 for ( c = 1 ;
 c < bs ;
 c ++ ) dst [ c ] = dst [ - 2 * stride + c - 1 ] ;
 dst += stride ;
 }
 }
 intra_pred_allsizes ( d117 ) static INLINE void d135_predictor ( uint8_t * dst , ptrdiff_t stride , int bs , const uint8_t * above , const uint8_t * left ) {
 int r , c ;
 dst [ 0 ] = ROUND_POWER_OF_TWO ( left [ 0 ] + above [ - 1 ] * 2 + above [ 0 ] , 2 ) ;
 for ( c = 1 ;
 c < bs ;
 c ++ ) dst [ c ] = ROUND_POWER_OF_TWO ( above [ c - 2 ] + above [ c - 1 ] * 2 + above [ c ] , 2 ) ;
 dst [ stride ] = ROUND_POWER_OF_TWO ( above [ - 1 ] + left [ 0 ] * 2 + left [ 1 ] , 2 ) ;
 for ( r = 2 ;
 r < bs ;
 ++ r ) dst [ r * stride ] = ROUND_POWER_OF_TWO ( left [ r - 2 ] + left [ r - 1 ] * 2 + left [ r ] , 2 ) ;
 dst += stride ;
 for ( r = 1 ;
 r < bs ;
 ++ r ) {
 for ( c = 1 ;
 c < bs ;
 c ++ ) dst [ c ] = dst [ - stride + c - 1 ] ;
 dst += stride ;
 }
 }
 intra_pred_allsizes ( d135 ) static INLINE void d153_predictor ( uint8_t * dst , ptrdiff_t stride , int bs , const uint8_t * above , const uint8_t * left ) {
 int r , c ;
 dst [ 0 ] = ROUND_POWER_OF_TWO ( above [ - 1 ] + left [ 0 ] , 1 ) ;
 for ( r = 1 ;
 r < bs ;
 r ++ ) dst [ r * stride ] = ROUND_POWER_OF_TWO ( left [ r - 1 ] + left [ r ] , 1 ) ;
 dst ++ ;
 dst [ 0 ] = ROUND_POWER_OF_TWO ( left [ 0 ] + above [ - 1 ] * 2 + above [ 0 ] , 2 ) ;
 dst [ stride ] = ROUND_POWER_OF_TWO ( above [ - 1 ] + left [ 0 ] * 2 + left [ 1 ] , 2 ) ;
 for ( r = 2 ;
 r < bs ;
 r ++ ) dst [ r * stride ] = ROUND_POWER_OF_TWO ( left [ r - 2 ] + left [ r - 1 ] * 2 + left [ r ] , 2 ) ;
 dst ++ ;
 for ( c = 0 ;
 c < bs - 2 ;
 c ++ ) dst [ c ] = ROUND_POWER_OF_TWO ( above [ c - 1 ] + above [ c ] * 2 + above [ c + 1 ] , 2 ) ;
 dst += stride ;
 for ( r = 1 ;
 r < bs ;
 ++ r ) {
 for ( c = 0 ;
 c < bs - 2 ;
 c ++ ) dst [ c ] = dst [ - stride + c - 2 ] ;
 dst += stride ;
 }
 }
 intra_pred_allsizes ( d153 )