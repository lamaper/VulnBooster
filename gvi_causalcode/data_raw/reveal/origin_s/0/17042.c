static void dissect_zcl_scenes_get_scene_membership_response ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 proto_item * scene_list ;
 proto_tree * scene_list_tree ;
 guint8 status , count , i ;
 status = tvb_get_guint8 ( tvb , * offset ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_scenes_status , tvb , * offset , 1 , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_scenes_capacity , tvb , * offset , 1 , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_scenes_group_id , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 if ( status == ZBEE_ZCL_STAT_SUCCESS ) {
 count = tvb_get_guint8 ( tvb , * offset ) ;
 proto_tree_add_uint ( tree , hf_zbee_zcl_scenes_scene_count , tvb , * offset , 1 , count ) ;
 * offset += 1 ;
 if ( count > 0 ) {
 scene_list = proto_tree_add_item ( tree , hf_zbee_zcl_scenes_scene_list , tvb , * offset , count , ENC_NA ) ;
 scene_list_tree = proto_item_add_subtree ( scene_list , ett_zbee_zcl_scenes_scene_ctrl ) ;
 for ( i = 0 ;
 i < count ;
 i ++ ) {
 proto_tree_add_item ( scene_list_tree , hf_zbee_zcl_scenes_scene_id , tvb , * offset , 1 , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 }
 }
 }
 }