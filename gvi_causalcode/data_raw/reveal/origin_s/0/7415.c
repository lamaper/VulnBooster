static PREDICTION_MODE read_intra_mode_y ( VP9_COMMON * cm , vp9_reader * r , int size_group ) {
 const PREDICTION_MODE y_mode = read_intra_mode ( r , cm -> fc . y_mode_prob [ size_group ] ) ;
 if ( ! cm -> frame_parallel_decoding_mode ) ++ cm -> counts . y_mode [ size_group ] [ y_mode ] ;
 return y_mode ;
 }