static void dissect_q931_information_rate_ie ( tvbuff_t * tvb , packet_info * pinfo , int offset , int len , proto_tree * tree , proto_item * item ) {
 if ( len != 4 ) {
 expert_add_info_format ( pinfo , item , & ei_q931_invalid_length , "Information rate: length is %d, should be 4" , len ) ;
 return ;
 }
 proto_tree_add_item ( tree , hf_q931_information_rate_incoming , tvb , offset + 0 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_q931_information_rate_outgoing , tvb , offset + 1 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_q931_information_rate_minimum_incoming , tvb , offset + 2 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_q931_information_rate_minimum_outgoing , tvb , offset + 3 , 1 , ENC_BIG_ENDIAN ) ;
 }