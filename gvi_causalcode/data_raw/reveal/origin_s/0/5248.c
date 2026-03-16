static void cmyk2bgr ( fz_context * ctx , fz_color_converter * cc , float * dv , const float * sv ) {

 cmyk_to_rgb ( ctx , NULL , sv , rgb ) ;
 dv [ 0 ] = rgb [ 2 ] ;
 dv [ 1 ] = rgb [ 1 ] ;
 dv [ 2 ] = rgb [ 0 ] ;

 dv [ 1 ] = 1 - fz_min ( sv [ 1 ] + sv [ 3 ] , 1 ) ;
 dv [ 2 ] = 1 - fz_min ( sv [ 0 ] + sv [ 3 ] , 1 ) ;
