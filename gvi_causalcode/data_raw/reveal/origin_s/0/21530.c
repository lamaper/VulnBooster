static void apply_ir_filter ( float * out , const AMRFixed * in , const float * filter ) {
 float filter1 [ AMR_SUBFRAME_SIZE ] , filter2 [ AMR_SUBFRAME_SIZE ] ;
 int lag = in -> pitch_lag ;
 float fac = in -> pitch_fac ;
 int i ;
 if ( lag < AMR_SUBFRAME_SIZE ) {
 ff_celp_circ_addf ( filter1 , filter , filter , lag , fac , AMR_SUBFRAME_SIZE ) ;
 if ( lag < AMR_SUBFRAME_SIZE >> 1 ) ff_celp_circ_addf ( filter2 , filter , filter1 , lag , fac , AMR_SUBFRAME_SIZE ) ;
 }
 memset ( out , 0 , sizeof ( float ) * AMR_SUBFRAME_SIZE ) ;
 for ( i = 0 ;
 i < in -> n ;
 i ++ ) {
 int x = in -> x [ i ] ;
 float y = in -> y [ i ] ;
 const float * filterp ;
 if ( x >= AMR_SUBFRAME_SIZE - lag ) {
 filterp = filter ;
 }
 else if ( x >= AMR_SUBFRAME_SIZE - ( lag << 1 ) ) {
 filterp = filter1 ;
 }
 else filterp = filter2 ;
 ff_celp_circ_addf ( out , out , filterp , x , y , AMR_SUBFRAME_SIZE ) ;
 }
 }