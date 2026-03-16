static inline void draw_n_color ( uint8_t * out , int stride , int width , int height , int bpp , uint8_t cols [ 4 ] , uint8_t grps [ 4 ] , uint32_t col ) {
 int x , y ;
 for ( y = 0 ;
 y < height ;
 y ++ ) {
 if ( grps ) cols [ 0 ] = grps [ 3 * ( y >> 1 ) ] ;
 for ( x = 0 ;
 x < width ;
 x ++ ) {
 if ( grps ) cols [ 1 ] = grps [ ( x >> 1 ) + 1 ] ;
 out [ x + y * stride ] = cols [ col & ( ( 1 << bpp ) - 1 ) ] ;
 col >>= bpp ;
 }
 }
 }