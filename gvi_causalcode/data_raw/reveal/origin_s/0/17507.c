static inline void put_pixels8x8_overlapped ( uint8_t * dst , uint8_t * src , int stride ) {
 uint8_t tmp [ 64 ] ;
 int i ;
 for ( i = 0 ;
 i < 8 ;
 i ++ ) memcpy ( tmp + i * 8 , src + i * stride , 8 ) ;
 for ( i = 0 ;
 i < 8 ;
 i ++ ) memcpy ( dst + i * stride , tmp + i * 8 , 8 ) ;
 }