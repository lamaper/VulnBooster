void proto_register_zbee_zcl_groups ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_zbee_zcl_groups_attr_id , {
 "Attribute" , "zbee_zcl_general.groups.attr_id" , FT_UINT16 , BASE_HEX , VALS ( zbee_zcl_groups_attr_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_groups_group_name_support , {
 "Group Name Support" , "zbee_zcl_general.groups.attr.group_name_support" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , ZBEE_ZCL_CMD_ID_GROUPS_NAME_SUPPORT_MASK , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_groups_group_id , {
 "Group ID" , "zbee_zcl_general.groups.group_id" , FT_UINT16 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_groups_group_list , {
 "Group List" , "zbee_zcl_general.groups.group_list" , FT_NONE , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_groups_group_count , {
 "Group Count" , "zbee_zcl_general.groups.group_count" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_groups_group_capacity , {
 "Group Capacity" , "zbee_zcl_general.groups.group_capacity" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_groups_status , {
 "Group Status" , "zbee_zcl_general.groups.group_status" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_status_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_groups_attr_str_len , {
 "Length" , "zbee_zcl_general.groups.attr_str_len" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_groups_attr_str , {
 "String" , "zbee_zcl_general.groups_attr_str" , FT_STRING , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_groups_srv_rx_cmd_id , {
 "Command" , "zbee_zcl_general.groups.cmd_srv_rx.id" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_groups_srv_rx_cmd_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_groups_srv_tx_cmd_id , {
 "Command" , "zbee_zcl_general.groups.cmd.srv_tx.id" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_groups_srv_tx_cmd_names ) , 0x00 , NULL , HFILL }
 }
 }
 ;
 static gint * ett [ ZBEE_ZCL_GROUPS_NUM_ETT ] ;
 ett [ 0 ] = & ett_zbee_zcl_groups ;
 ett [ 1 ] = & ett_zbee_zcl_groups_grp_ctrl ;
 proto_zbee_zcl_groups = proto_register_protocol ( "ZigBee ZCL Groups" , "ZCL Groups" , ZBEE_PROTOABBREV_ZCL_GROUPS ) ;
 proto_register_field_array ( proto_zbee_zcl_groups , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 register_dissector ( ZBEE_PROTOABBREV_ZCL_GROUPS , dissect_zbee_zcl_groups , proto_zbee_zcl_groups ) ;
 }