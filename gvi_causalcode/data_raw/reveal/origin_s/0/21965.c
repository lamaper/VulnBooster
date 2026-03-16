static void dissect_zcl_scenes_remove_all_get_scene_membership ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 proto_tree_add_item ( tree , hf_zbee_zcl_scenes_group_id , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 }