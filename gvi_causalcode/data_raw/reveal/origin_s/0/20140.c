static int get_aq_c_strength ( int q_index , vpx_bit_depth_t bit_depth ) {
 const int base_quant = vp9_ac_quant ( q_index , 0 , bit_depth ) / 4 ;
 return ( base_quant > 20 ) + ( base_quant > 45 ) ;
 }