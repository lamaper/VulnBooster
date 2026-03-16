struct matrix build_colorant_matrix ( qcms_profile * p ) {
 struct matrix result ;
 result . m [ 0 ] [ 0 ] = s15Fixed16Number_to_float ( p -> redColorant . X ) ;
 result . m [ 0 ] [ 1 ] = s15Fixed16Number_to_float ( p -> greenColorant . X ) ;
 result . m [ 0 ] [ 2 ] = s15Fixed16Number_to_float ( p -> blueColorant . X ) ;
 result . m [ 1 ] [ 0 ] = s15Fixed16Number_to_float ( p -> redColorant . Y ) ;
 result . m [ 1 ] [ 1 ] = s15Fixed16Number_to_float ( p -> greenColorant . Y ) ;
 result . m [ 1 ] [ 2 ] = s15Fixed16Number_to_float ( p -> blueColorant . Y ) ;
 result . m [ 2 ] [ 0 ] = s15Fixed16Number_to_float ( p -> redColorant . Z ) ;
 result . m [ 2 ] [ 1 ] = s15Fixed16Number_to_float ( p -> greenColorant . Z ) ;
 result . m [ 2 ] [ 2 ] = s15Fixed16Number_to_float ( p -> blueColorant . Z ) ;
 result . invalid = false ;
 return result ;
 }