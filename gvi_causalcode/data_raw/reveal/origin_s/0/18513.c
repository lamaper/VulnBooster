static void nb_call_name_type ( tvbuff_t * tvb , int offset , proto_tree * tree ) {
 proto_tree_add_item ( tree , hf_netb_call_name_type , tvb , offset + NB_CALL_NAME_TYPE , 1 , ENC_LITTLE_ENDIAN ) ;
 }