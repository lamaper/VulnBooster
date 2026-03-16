static int cinepak_decode_vectors ( CinepakContext * s , cvid_strip * strip , int chunk_id , int size , const uint8_t * data ) {
 const uint8_t * eod = ( data + size ) ;
 uint32_t flag , mask ;
 cvid_codebook * codebook ;
 unsigned int x , y ;
 uint32_t iy [ 4 ] ;
 uint32_t iu [ 2 ] ;
 uint32_t iv [ 2 ] ;
 flag = 0 ;
 mask = 0 ;
 for ( y = strip -> y1 ;
 y < strip -> y2 ;
 y += 4 ) {
 iy [ 0 ] = strip -> x1 + ( y * s -> frame . linesize [ 0 ] ) ;
 iy [ 1 ] = iy [ 0 ] + s -> frame . linesize [ 0 ] ;
 iy [ 2 ] = iy [ 1 ] + s -> frame . linesize [ 0 ] ;
 iy [ 3 ] = iy [ 2 ] + s -> frame . linesize [ 0 ] ;
 iu [ 0 ] = ( strip -> x1 / 2 ) + ( ( y / 2 ) * s -> frame . linesize [ 1 ] ) ;
 iu [ 1 ] = iu [ 0 ] + s -> frame . linesize [ 1 ] ;
 iv [ 0 ] = ( strip -> x1 / 2 ) + ( ( y / 2 ) * s -> frame . linesize [ 2 ] ) ;
 iv [ 1 ] = iv [ 0 ] + s -> frame . linesize [ 2 ] ;
 for ( x = strip -> x1 ;
 x < strip -> x2 ;
 x += 4 ) {
 if ( ( chunk_id & 0x01 ) && ! ( mask >>= 1 ) ) {
 if ( ( data + 4 ) > eod ) return AVERROR_INVALIDDATA ;
 flag = AV_RB32 ( data ) ;
 data += 4 ;
 mask = 0x80000000 ;
 }
 if ( ! ( chunk_id & 0x01 ) || ( flag & mask ) ) {
 if ( ! ( chunk_id & 0x02 ) && ! ( mask >>= 1 ) ) {
 if ( ( data + 4 ) > eod ) return AVERROR_INVALIDDATA ;
 flag = AV_RB32 ( data ) ;
 data += 4 ;
 mask = 0x80000000 ;
 }
 if ( ( chunk_id & 0x02 ) || ( ~ flag & mask ) ) {
 if ( data >= eod ) return AVERROR_INVALIDDATA ;
 codebook = & strip -> v1_codebook [ * data ++ ] ;
 s -> frame . data [ 0 ] [ iy [ 0 ] + 0 ] = codebook -> y0 ;
 s -> frame . data [ 0 ] [ iy [ 0 ] + 1 ] = codebook -> y0 ;
 s -> frame . data [ 0 ] [ iy [ 1 ] + 0 ] = codebook -> y0 ;
 s -> frame . data [ 0 ] [ iy [ 1 ] + 1 ] = codebook -> y0 ;
 if ( ! s -> palette_video ) {
 s -> frame . data [ 1 ] [ iu [ 0 ] ] = codebook -> u ;
 s -> frame . data [ 2 ] [ iv [ 0 ] ] = codebook -> v ;
 }
 s -> frame . data [ 0 ] [ iy [ 0 ] + 2 ] = codebook -> y1 ;
 s -> frame . data [ 0 ] [ iy [ 0 ] + 3 ] = codebook -> y1 ;
 s -> frame . data [ 0 ] [ iy [ 1 ] + 2 ] = codebook -> y1 ;
 s -> frame . data [ 0 ] [ iy [ 1 ] + 3 ] = codebook -> y1 ;
 if ( ! s -> palette_video ) {
 s -> frame . data [ 1 ] [ iu [ 0 ] + 1 ] = codebook -> u ;
 s -> frame . data [ 2 ] [ iv [ 0 ] + 1 ] = codebook -> v ;
 }
 s -> frame . data [ 0 ] [ iy [ 2 ] + 0 ] = codebook -> y2 ;
 s -> frame . data [ 0 ] [ iy [ 2 ] + 1 ] = codebook -> y2 ;
 s -> frame . data [ 0 ] [ iy [ 3 ] + 0 ] = codebook -> y2 ;
 s -> frame . data [ 0 ] [ iy [ 3 ] + 1 ] = codebook -> y2 ;
 if ( ! s -> palette_video ) {
 s -> frame . data [ 1 ] [ iu [ 1 ] ] = codebook -> u ;
 s -> frame . data [ 2 ] [ iv [ 1 ] ] = codebook -> v ;
 }
 s -> frame . data [ 0 ] [ iy [ 2 ] + 2 ] = codebook -> y3 ;
 s -> frame . data [ 0 ] [ iy [ 2 ] + 3 ] = codebook -> y3 ;
 s -> frame . data [ 0 ] [ iy [ 3 ] + 2 ] = codebook -> y3 ;
 s -> frame . data [ 0 ] [ iy [ 3 ] + 3 ] = codebook -> y3 ;
 if ( ! s -> palette_video ) {
 s -> frame . data [ 1 ] [ iu [ 1 ] + 1 ] = codebook -> u ;
 s -> frame . data [ 2 ] [ iv [ 1 ] + 1 ] = codebook -> v ;
 }
 }
 else if ( flag & mask ) {
 if ( ( data + 4 ) > eod ) return AVERROR_INVALIDDATA ;
 codebook = & strip -> v4_codebook [ * data ++ ] ;
 s -> frame . data [ 0 ] [ iy [ 0 ] + 0 ] = codebook -> y0 ;
 s -> frame . data [ 0 ] [ iy [ 0 ] + 1 ] = codebook -> y1 ;
 s -> frame . data [ 0 ] [ iy [ 1 ] + 0 ] = codebook -> y2 ;
 s -> frame . data [ 0 ] [ iy [ 1 ] + 1 ] = codebook -> y3 ;
 if ( ! s -> palette_video ) {
 s -> frame . data [ 1 ] [ iu [ 0 ] ] = codebook -> u ;
 s -> frame . data [ 2 ] [ iv [ 0 ] ] = codebook -> v ;
 }
 codebook = & strip -> v4_codebook [ * data ++ ] ;
 s -> frame . data [ 0 ] [ iy [ 0 ] + 2 ] = codebook -> y0 ;
 s -> frame . data [ 0 ] [ iy [ 0 ] + 3 ] = codebook -> y1 ;
 s -> frame . data [ 0 ] [ iy [ 1 ] + 2 ] = codebook -> y2 ;
 s -> frame . data [ 0 ] [ iy [ 1 ] + 3 ] = codebook -> y3 ;
 if ( ! s -> palette_video ) {
 s -> frame . data [ 1 ] [ iu [ 0 ] + 1 ] = codebook -> u ;
 s -> frame . data [ 2 ] [ iv [ 0 ] + 1 ] = codebook -> v ;
 }
 codebook = & strip -> v4_codebook [ * data ++ ] ;
 s -> frame . data [ 0 ] [ iy [ 2 ] + 0 ] = codebook -> y0 ;
 s -> frame . data [ 0 ] [ iy [ 2 ] + 1 ] = codebook -> y1 ;
 s -> frame . data [ 0 ] [ iy [ 3 ] + 0 ] = codebook -> y2 ;
 s -> frame . data [ 0 ] [ iy [ 3 ] + 1 ] = codebook -> y3 ;
 if ( ! s -> palette_video ) {
 s -> frame . data [ 1 ] [ iu [ 1 ] ] = codebook -> u ;
 s -> frame . data [ 2 ] [ iv [ 1 ] ] = codebook -> v ;
 }
 codebook = & strip -> v4_codebook [ * data ++ ] ;
 s -> frame . data [ 0 ] [ iy [ 2 ] + 2 ] = codebook -> y0 ;
 s -> frame . data [ 0 ] [ iy [ 2 ] + 3 ] = codebook -> y1 ;
 s -> frame . data [ 0 ] [ iy [ 3 ] + 2 ] = codebook -> y2 ;
 s -> frame . data [ 0 ] [ iy [ 3 ] + 3 ] = codebook -> y3 ;
 if ( ! s -> palette_video ) {
 s -> frame . data [ 1 ] [ iu [ 1 ] + 1 ] = codebook -> u ;
 s -> frame . data [ 2 ] [ iv [ 1 ] + 1 ] = codebook -> v ;
 }
 }
 }
 iy [ 0 ] += 4 ;
 iy [ 1 ] += 4 ;
 iy [ 2 ] += 4 ;
 iy [ 3 ] += 4 ;
 iu [ 0 ] += 2 ;
 iu [ 1 ] += 2 ;
 iv [ 0 ] += 2 ;
 iv [ 1 ] += 2 ;
 }
 }
 return 0 ;
 }