static void backward_filter ( RA288Context * ractx , float * hist , float * rec , const float * window , float * lpc , const float * tab , int order , int n , int non_rec , int move_size ) {
 float temp [ MAX_BACKWARD_FILTER_ORDER + 1 ] ;
 do_hybrid_window ( ractx , order , n , non_rec , temp , hist , rec , window ) ;
 if ( ! compute_lpc_coefs ( temp , order , lpc , 0 , 1 , 1 ) ) ractx -> fdsp . vector_fmul ( lpc , lpc , tab , FFALIGN ( order , 16 ) ) ;
 memmove ( hist , hist + n , move_size * sizeof ( * hist ) ) ;
 }