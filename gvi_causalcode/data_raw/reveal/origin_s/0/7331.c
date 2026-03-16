void mem_swap_byte_rect ( byte * base , uint raster , int x , int w , int h , bool store ) {
 int xbit = x & 31 ;
 if ( store ) {
 if ( xbit + w > 64 ) {
 if ( xbit != 0 ) mem_swap_byte_rect ( base , raster , x , 1 , h , false ) ;
 x += w - 1 ;
 xbit = x & 31 ;
 if ( xbit == 31 ) return ;
 w = 1 ;
 }
 }
 {
 byte * row = base + ( ( x >> 5 ) << 2 ) ;
 int nw = ( xbit + w + 31 ) >> 5 ;
 int ny ;
 for ( ny = h ;
 ny > 0 ;
 row += raster , -- ny ) {
 int nx = nw ;
 bits32 * pw = ( bits32 * ) row ;
 do {
 bits32 w = * pw ;
 * pw ++ = ( w >> 24 ) + ( ( w >> 8 ) & 0xff00 ) + ( ( w & 0xff00 ) << 8 ) + ( w << 24 ) ;
 }
 while ( -- nx ) ;
 }
 }
 }