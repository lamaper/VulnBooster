int vp9_qindex_to_quantizer ( int qindex ) {
 int quantizer ;
 for ( quantizer = 0 ;
 quantizer < 64 ;
 ++ quantizer ) if ( quantizer_to_qindex [ quantizer ] >= qindex ) return quantizer ;
 return 63 ;
 }