static void dissect_zcl_groups_get_group_membership ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 proto_item * grp_list ;
 proto_tree * grp_list_tree ;
 guint8 count , i ;
 count = tvb_get_guint8 ( tvb , * offset ) ;
 proto_tree_add_uint ( tree , hf_zbee_zcl_groups_group_count , tvb , * offset , 1 , count ) ;
 * offset += 1 ;
 if ( count > 0 ) {
 grp_list = proto_tree_add_item ( tree , hf_zbee_zcl_groups_group_list , tvb , * offset , 2 * count , ENC_NA ) ;
 grp_list_tree = proto_item_add_subtree ( grp_list , ett_zbee_zcl_groups_grp_ctrl ) ;
 for ( i = 0 ;
 i < count ;
 i ++ ) {
 proto_tree_add_item ( grp_list_tree , hf_zbee_zcl_groups_group_id , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 }
 }
 }