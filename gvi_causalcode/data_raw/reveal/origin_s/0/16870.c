static void postfilter ( QCELPContext * q , float * samples , float * lpc ) {
 static const float pow_0_775 [ 10 ] = {
 0.775000 , 0.600625 , 0.465484 , 0.360750 , 0.279582 , 0.216676 , 0.167924 , 0.130141 , 0.100859 , 0.078166 }
 , pow_0_625 [ 10 ] = {
 0.625000 , 0.390625 , 0.244141 , 0.152588 , 0.095367 , 0.059605 , 0.037253 , 0.023283 , 0.014552 , 0.009095 }
 ;
 float lpc_s [ 10 ] , lpc_p [ 10 ] , pole_out [ 170 ] , zero_out [ 160 ] ;
 int n ;
 for ( n = 0 ;
 n < 10 ;
 n ++ ) {
 lpc_s [ n ] = lpc [ n ] * pow_0_625 [ n ] ;
 lpc_p [ n ] = lpc [ n ] * pow_0_775 [ n ] ;
 }
 ff_celp_lp_zero_synthesis_filterf ( zero_out , lpc_s , q -> formant_mem + 10 , 160 , 10 ) ;
 memcpy ( pole_out , q -> postfilter_synth_mem , sizeof ( float ) * 10 ) ;
 ff_celp_lp_synthesis_filterf ( pole_out + 10 , lpc_p , zero_out , 160 , 10 ) ;
 memcpy ( q -> postfilter_synth_mem , pole_out + 160 , sizeof ( float ) * 10 ) ;
 ff_tilt_compensation ( & q -> postfilter_tilt_mem , 0.3 , pole_out + 10 , 160 ) ;
 ff_adaptive_gain_control ( samples , pole_out + 10 , avpriv_scalarproduct_float_c ( q -> formant_mem + 10 , q -> formant_mem + 10 , 160 ) , 160 , 0.9375 , & q -> postfilter_agc_mem ) ;
 }