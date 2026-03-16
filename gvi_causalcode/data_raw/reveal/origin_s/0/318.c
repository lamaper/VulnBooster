static void dissect_q931_pl_binary_parameters_ie ( tvbuff_t * tvb , int offset , int len , proto_tree * tree ) {
 const int * fields [ ] = {
 & hf_q931_fast_select , & hf_q931_pl_request , & hf_q931_pl_binary_confirmation , & hf_q931_pl_modulus , NULL }
 ;
 if ( len == 0 ) return ;
 proto_tree_add_bitmask_list ( tree , tvb , offset , 1 , fields , ENC_NA ) ;
 }