static int dissect_sercosiii_link_error_count_p1p2 ( packet_info * pinfo , proto_tree * tree , proto_item * item , tvbuff_t * tvb , int offset , int total_len ) {
 if ( total_len < 4 ) {
 expert_add_info ( pinfo , item , & ei_mal_sercosiii_link_error_count_p1p2 ) ;
 return total_len ;
 }
 proto_tree_add_item ( tree , hf_cip_sercosiii_link_error_count_p1 , tvb , offset , 2 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cip_sercosiii_link_error_count_p2 , tvb , offset + 2 , 2 , ENC_LITTLE_ENDIAN ) ;
 return 4 ;
 }