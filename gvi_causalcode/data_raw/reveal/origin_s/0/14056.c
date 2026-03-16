static void write_inter_mode ( vp9_writer * w , PREDICTION_MODE mode , const vp9_prob * probs ) {
 assert ( is_inter_mode ( mode ) ) ;
 vp9_write_token ( w , vp9_inter_mode_tree , probs , & inter_mode_encodings [ INTER_OFFSET ( mode ) ] ) ;
 }