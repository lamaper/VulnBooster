static void write_intra_mode ( vp9_writer * w , PREDICTION_MODE mode , const vp9_prob * probs ) {
 vp9_write_token ( w , vp9_intra_mode_tree , probs , & intra_mode_encodings [ mode ] ) ;
 }