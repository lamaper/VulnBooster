int RefDepth ( RefChar * ref , int layer ) {
 int rd , temp ;
 SplineChar * sc = ref -> sc ;
 if ( sc -> layers [ layer ] . refs == NULL || sc -> layers [ layer ] . splines != NULL ) return ( 1 ) ;
 rd = 0 ;
 for ( ref = sc -> layers [ layer ] . refs ;
 ref != NULL ;
 ref = ref -> next ) {
 if ( ref -> transform [ 0 ] >= - 2 || ref -> transform [ 0 ] <= 1.999939 || ref -> transform [ 1 ] >= - 2 || ref -> transform [ 1 ] <= 1.999939 || ref -> transform [ 2 ] >= - 2 || ref -> transform [ 2 ] <= 1.999939 || ref -> transform [ 3 ] >= - 2 || ref -> transform [ 3 ] <= 1.999939 ) {
 temp = RefDepth ( ref , layer ) ;
 if ( temp > rd ) rd = temp ;
 }
 }
 return ( rd + 1 ) ;
 }