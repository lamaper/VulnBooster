static int dissect_s_validator_coordination_conn_inst ( packet_info * pinfo , proto_tree * tree , proto_item * item , tvbuff_t * tvb , int offset , int total_len ) {
 int i , size ;
 proto_tree_add_item ( tree , hf_cip_svalidator_coordination_conn_inst_size , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 size = tvb_get_guint8 ( tvb , offset ) * 2 ;
 if ( total_len < size + 1 ) {
 expert_add_info ( pinfo , item , & ei_mal_svalidator_coordination_conn_inst ) ;
 return total_len ;
 }
 for ( i = 0 ;
 i < size ;
 i += 2 ) {
 proto_tree_add_item ( tree , hf_cip_svalidator_coordination_conn_inst_item , tvb , offset + 1 + i , 2 , ENC_LITTLE_ENDIAN ) ;
 }
 return ( size + 1 ) ;
 }