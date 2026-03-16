static void pitch_sharpening ( AMRContext * p , int subframe , enum Mode mode , AMRFixed * fixed_sparse ) {
 if ( mode == MODE_12k2 ) p -> beta = FFMIN ( p -> pitch_gain [ 4 ] , 1.0 ) ;
 fixed_sparse -> pitch_lag = p -> pitch_lag_int ;
 fixed_sparse -> pitch_fac = p -> beta ;
 if ( mode != MODE_4k75 || subframe & 1 ) p -> beta = av_clipf ( p -> pitch_gain [ 4 ] , 0.0 , SHARP_MAX ) ;
 }