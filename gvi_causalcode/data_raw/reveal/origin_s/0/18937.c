void dissect_zcl_scenes_attr_data ( proto_tree * tree , tvbuff_t * tvb , guint * offset , guint16 attr_id , guint data_type ) {
 switch ( attr_id ) {
 case ZBEE_ZCL_ATTR_ID_SCENES_SCENE_VALID : proto_tree_add_item ( tree , hf_zbee_zcl_scenes_attr_id_scene_valid , tvb , * offset , 1 , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_SCENES_NAME_SUPPORT : proto_tree_add_item ( tree , hf_zbee_zcl_scenes_attr_id_name_support , tvb , * offset , 1 , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_SCENES_SCENE_COUNT : case ZBEE_ZCL_ATTR_ID_SCENES_CURRENT_SCENE : case ZBEE_ZCL_ATTR_ID_SCENES_CURRENT_GROUP : case ZBEE_ZCL_ATTR_ID_SCENES_LAST_CONFIGURED_BY : default : dissect_zcl_attr_data ( tvb , tree , offset , data_type ) ;
 break ;
 }
 }