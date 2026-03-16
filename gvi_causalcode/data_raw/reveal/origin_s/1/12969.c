int16_t vp9_dc_quant ( int qindex , int delta ) {
 return dc_qlookup [ clamp ( qindex + delta , 0 , MAXQ ) ] ;
 }