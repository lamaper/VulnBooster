static void nb_resp_corrl ( tvbuff_t * tvb , int offset , proto_tree * tree ) {
 proto_tree_add_item ( tree , hf_netb_resp_corrl , tvb , offset + NB_RESP_CORL , 2 , ENC_LITTLE_ENDIAN ) ;
 }