static void dissect_zcl_groups_add_remove_group_response ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 proto_tree_add_item ( tree , hf_zbee_zcl_groups_status , tvb , * offset , 1 , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_groups_group_id , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 }