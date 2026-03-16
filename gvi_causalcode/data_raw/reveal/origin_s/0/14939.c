static void nb_xmit_corrl ( tvbuff_t * tvb , int offset , proto_tree * tree ) {
 proto_tree_add_item ( tree , hf_netb_xmit_corrl , tvb , offset + NB_XMIT_CORL , 2 , ENC_LITTLE_ENDIAN ) ;
 }