static void nb_data1 ( int hf , tvbuff_t * tvb , int offset , proto_tree * tree ) {
 proto_tree_add_item ( tree , hf , tvb , offset + NB_DATA1 , 1 , ENC_LITTLE_ENDIAN ) ;
 }