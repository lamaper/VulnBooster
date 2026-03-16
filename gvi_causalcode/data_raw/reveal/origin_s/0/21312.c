static int conditional_skipintra ( PREDICTION_MODE mode , PREDICTION_MODE best_intra_mode ) {
 if ( mode == D117_PRED && best_intra_mode != V_PRED && best_intra_mode != D135_PRED ) return 1 ;
 if ( mode == D63_PRED && best_intra_mode != V_PRED && best_intra_mode != D45_PRED ) return 1 ;
 if ( mode == D207_PRED && best_intra_mode != H_PRED && best_intra_mode != D45_PRED ) return 1 ;
 if ( mode == D153_PRED && best_intra_mode != H_PRED && best_intra_mode != D135_PRED ) return 1 ;
 return 0 ;
 }