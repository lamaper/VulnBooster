static float tilt_factor ( const float * lpcs , int n_lpcs ) {
 float rh0 , rh1 ;
 rh0 = 1.0 + avpriv_scalarproduct_float_c ( lpcs , lpcs , n_lpcs ) ;
 rh1 = lpcs [ 0 ] + avpriv_scalarproduct_float_c ( lpcs , & lpcs [ 1 ] , n_lpcs - 1 ) ;
 return rh1 / rh0 ;
 }