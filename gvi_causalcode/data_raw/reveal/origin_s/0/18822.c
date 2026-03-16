static PREDICTION_MODE read_intra_mode_uv ( VP9_COMMON * cm , vp9_reader * r , PREDICTION_MODE y_mode ) {
 const PREDICTION_MODE uv_mode = read_intra_mode ( r , cm -> fc . uv_mode_prob [ y_mode ] ) ;
 if ( ! cm -> frame_parallel_decoding_mode ) ++ cm -> counts . uv_mode [ y_mode ] [ uv_mode ] ;
 return uv_mode ;
 }