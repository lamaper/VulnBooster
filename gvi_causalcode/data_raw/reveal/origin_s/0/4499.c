static PREDICTION_MODE read_inter_mode ( VP9_COMMON * cm , vp9_reader * r , int ctx ) {
 const int mode = vp9_read_tree ( r , vp9_inter_mode_tree , cm -> fc . inter_mode_probs [ ctx ] ) ;
 if ( ! cm -> frame_parallel_decoding_mode ) ++ cm -> counts . inter_mode [ ctx ] [ mode ] ;
 return NEARESTMV + mode ;
 }