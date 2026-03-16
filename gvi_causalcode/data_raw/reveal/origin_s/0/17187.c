static void exchange_uv ( MpegEncContext * s ) {
 int16_t ( * tmp ) [ 64 ] ;
 tmp = s -> pblocks [ 4 ] ;
 s -> pblocks [ 4 ] = s -> pblocks [ 5 ] ;
 s -> pblocks [ 5 ] = tmp ;
 }