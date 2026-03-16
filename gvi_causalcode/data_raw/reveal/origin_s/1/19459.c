static int get_aq_c_strength ( int q_index ) {
 int base_quant = vp9_ac_quant ( q_index , 0 ) / 4 ;
 return ( base_quant > 20 ) + ( base_quant > 45 ) ;
 }