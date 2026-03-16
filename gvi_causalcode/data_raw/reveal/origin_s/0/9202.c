void ff_mpeg1_clean_buffers ( MpegEncContext * s ) {
 s -> last_dc [ 0 ] = 1 << ( 7 + s -> intra_dc_precision ) ;
 s -> last_dc [ 1 ] = s -> last_dc [ 0 ] ;
 s -> last_dc [ 2 ] = s -> last_dc [ 0 ] ;
 memset ( s -> last_mv , 0 , sizeof ( s -> last_mv ) ) ;
 }