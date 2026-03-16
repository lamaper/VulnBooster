static int decode_blockcode ( int code , int levels , int * values ) {
 int i ;
 int offset = ( levels - 1 ) >> 1 ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 int div = FASTDIV ( code , levels ) ;
 values [ i ] = code - offset - div * levels ;
 code = div ;
 }
 return code ;
 }