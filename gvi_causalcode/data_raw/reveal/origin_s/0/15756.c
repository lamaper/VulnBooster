static void vc2_subband_dwt_haar ( VC2TransformContext * t , dwtcoef * data , ptrdiff_t stride , int width , int height ) {
 dwt_haar ( t , data , stride , width , height , 0 ) ;
 }