static struct matrix build_lut_matrix ( struct lutType * lut ) {
 struct matrix result ;
 if ( lut ) {
 result . m [ 0 ] [ 0 ] = s15Fixed16Number_to_float ( lut -> e00 ) ;
 result . m [ 0 ] [ 1 ] = s15Fixed16Number_to_float ( lut -> e01 ) ;
 result . m [ 0 ] [ 2 ] = s15Fixed16Number_to_float ( lut -> e02 ) ;
 result . m [ 1 ] [ 0 ] = s15Fixed16Number_to_float ( lut -> e10 ) ;
 result . m [ 1 ] [ 1 ] = s15Fixed16Number_to_float ( lut -> e11 ) ;
 result . m [ 1 ] [ 2 ] = s15Fixed16Number_to_float ( lut -> e12 ) ;
 result . m [ 2 ] [ 0 ] = s15Fixed16Number_to_float ( lut -> e20 ) ;
 result . m [ 2 ] [ 1 ] = s15Fixed16Number_to_float ( lut -> e21 ) ;
 result . m [ 2 ] [ 2 ] = s15Fixed16Number_to_float ( lut -> e22 ) ;
 result . invalid = false ;
 }
 else {
 memset ( & result , 0 , sizeof ( struct matrix ) ) ;
 result . invalid = true ;
 }
 return result ;
 }