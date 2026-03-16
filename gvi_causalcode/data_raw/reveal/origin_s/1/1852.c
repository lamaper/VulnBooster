int16_t vp9_ac_quant ( int qindex , int delta ) {
 return ac_qlookup [ clamp ( qindex + delta , 0 , MAXQ ) ] ;
 }