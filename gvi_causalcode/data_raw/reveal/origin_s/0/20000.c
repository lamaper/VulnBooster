static void cmyk2rgb ( fz_context * ctx , fz_color_converter * cc , float * dv , const float * sv ) {


 dv [ 1 ] = 1 - fz_min ( sv [ 1 ] + sv [ 3 ] , 1 ) ;
 dv [ 2 ] = 1 - fz_min ( sv [ 2 ] + sv [ 3 ] , 1 ) ;
