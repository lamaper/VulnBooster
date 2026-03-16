static void do_hybrid_window ( RA288Context * ractx , int order , int n , int non_rec , float * out , float * hist , float * out2 , const float * window ) {
 int i ;
 float buffer1 [ MAX_BACKWARD_FILTER_ORDER + 1 ] ;
 float buffer2 [ MAX_BACKWARD_FILTER_ORDER + 1 ] ;
 LOCAL_ALIGNED ( 32 , float , work , [ FFALIGN ( MAX_BACKWARD_FILTER_ORDER + MAX_BACKWARD_FILTER_LEN + MAX_BACKWARD_FILTER_NONREC , 16 ) ] ) ;
 ractx -> fdsp . vector_fmul ( work , window , hist , FFALIGN ( order + n + non_rec , 16 ) ) ;
 convolve ( buffer1 , work + order , n , order ) ;
 convolve ( buffer2 , work + order + n , non_rec , order ) ;
 for ( i = 0 ;
 i <= order ;
 i ++ ) {
 out2 [ i ] = out2 [ i ] * 0.5625 + buffer1 [ i ] ;
 out [ i ] = out2 [ i ] + buffer2 [ i ] ;
 }
 * out *= 257. / 256. ;
 }