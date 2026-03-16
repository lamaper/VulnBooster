static int IsTTFRefable ( SplineChar * sc , int layer ) {
 RefChar * ref ;
 if ( sc -> layers [ layer ] . refs == NULL || sc -> layers [ layer ] . splines != NULL ) return ( false ) ;
 for ( ref = sc -> layers [ layer ] . refs ;
 ref != NULL ;
 ref = ref -> next ) {
 if ( ref -> transform [ 0 ] < - 2 || ref -> transform [ 0 ] > 1.999939 || ref -> transform [ 1 ] < - 2 || ref -> transform [ 1 ] > 1.999939 || ref -> transform [ 2 ] < - 2 || ref -> transform [ 2 ] > 1.999939 || ref -> transform [ 3 ] < - 2 || ref -> transform [ 3 ] > 1.999939 ) return ( false ) ;
 }
 return ( true ) ;
 }