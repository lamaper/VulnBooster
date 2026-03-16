void dissect_zcl_groups_attr_data ( proto_tree * tree , tvbuff_t * tvb , guint * offset , guint16 attr_id , guint data_type ) {
 switch ( attr_id ) {
 case ZBEE_ZCL_ATTR_ID_GROUPS_NAME_SUPPORT : proto_tree_add_item ( tree , hf_zbee_zcl_groups_group_name_support , tvb , * offset , 1 , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 break ;
 default : dissect_zcl_attr_data ( tvb , tree , offset , data_type ) ;
 break ;
 }
 }