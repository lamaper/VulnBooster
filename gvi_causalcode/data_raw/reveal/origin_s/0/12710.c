void ff_mpeg4_clean_buffers ( MpegEncContext * s ) {
 int c_wrap , c_xy , l_wrap , l_xy ;
 l_wrap = s -> b8_stride ;
 l_xy = ( 2 * s -> mb_y - 1 ) * l_wrap + s -> mb_x * 2 - 1 ;
 c_wrap = s -> mb_stride ;
 c_xy = ( s -> mb_y - 1 ) * c_wrap + s -> mb_x - 1 ;

 memsetw ( s -> dc_val [ 1 ] + c_xy , 1024 , c_wrap + 1 ) ;
 memsetw ( s -> dc_val [ 2 ] + c_xy , 1024 , c_wrap + 1 ) ;

 memset ( s -> ac_val [ 1 ] + c_xy , 0 , ( c_wrap + 1 ) * 16 * sizeof ( int16_t ) ) ;
 memset ( s -> ac_val [ 2 ] + c_xy , 0 , ( c_wrap + 1 ) * 16 * sizeof ( int16_t ) ) ;
 s -> last_mv [ 0 ] [ 0 ] [ 0 ] = s -> last_mv [ 0 ] [ 0 ] [ 1 ] = s -> last_mv [ 1 ] [ 0 ] [ 0 ] = s -> last_mv [ 1 ] [ 0 ] [ 1 ] = 0 ;
 }