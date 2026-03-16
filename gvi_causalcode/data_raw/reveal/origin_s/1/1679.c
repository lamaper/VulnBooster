double vp9_convert_qindex_to_q ( int qindex ) {
 return vp9_ac_quant ( qindex , 0 ) / 4.0 ;
 }