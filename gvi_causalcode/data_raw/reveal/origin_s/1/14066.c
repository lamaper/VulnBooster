void vp9_ ## type ## _predictor_ ## size ## x ## size ## _c ( uint8_t * dst , ptrdiff_t stride , const uint8_t * above , const uint8_t * left ) {
 type ## _predictor ( dst , stride , size , above , left ) ;
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
 intra_pred_allsizes ( d153 ) static INLINE void v_predictor ( uint8_t * dst , ptrdiff_t stride , int bs , const uint8_t * above , const uint8_t * left ) {
 int r ;
 ( void ) left ;
 for ( r = 0 ;
 r < bs ;
 r ++ ) {
 vpx_memcpy ( dst , above , bs ) ;
 dst += stride ;
 }
 }
 intra_pred_allsizes ( v ) static INLINE void h_predictor ( uint8_t * dst , ptrdiff_t stride , int bs , const uint8_t * above , const uint8_t * left ) {
 int r ;
 ( void ) above ;
 for ( r = 0 ;
 r < bs ;
 r ++ ) {
 vpx_memset ( dst , left [ r ] , bs ) ;
 dst += stride ;
 }
 }
 intra_pred_allsizes ( h ) static INLINE void tm_predictor ( uint8_t * dst , ptrdiff_t stride , int bs , const uint8_t * above , const uint8_t * left ) {
 int r , c ;
 int ytop_left = above [ - 1 ] ;
 for ( r = 0 ;
 r < bs ;
 r ++ ) {
 for ( c = 0 ;
 c < bs ;
 c ++ ) dst [ c ] = clip_pixel ( left [ r ] + above [ c ] - ytop_left ) ;
 dst += stride ;
 }
 }
 intra_pred_allsizes ( tm ) static INLINE void dc_128_predictor ( uint8_t * dst , ptrdiff_t stride , int bs , const uint8_t * above , const uint8_t * left ) {
 int r ;
 ( void ) above ;
 ( void ) left ;
 for ( r = 0 ;
 r < bs ;
 r ++ ) {
 vpx_memset ( dst , 128 , bs ) ;
 dst += stride ;
 }
 }
 intra_pred_allsizes ( dc_128 )