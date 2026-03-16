static int find_fp_qindex ( ) {
 int i ;
 for ( i = 0 ;
 i < QINDEX_RANGE ;
 ++ i ) if ( vp9_convert_qindex_to_q ( i ) >= 30.0 ) break ;
 if ( i == QINDEX_RANGE ) i -- ;
 return i ;
 }