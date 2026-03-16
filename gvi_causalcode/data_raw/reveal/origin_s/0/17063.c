static void nb_data2 ( int hf , tvbuff_t * tvb , int offset , proto_tree * tree ) {
 proto_tree_add_item ( tree , hf , tvb , offset + NB_DATA2 , 2 , ENC_LITTLE_ENDIAN ) ;
 }