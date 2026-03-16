void proto_register_zbee_zcl_scenes ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_zbee_zcl_scenes_attr_id , {
 "Attribute" , "zbee_zcl_general.scenes.attr_id" , FT_UINT16 , BASE_HEX , VALS ( zbee_zcl_scenes_attr_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_scenes_scene_list , {
 "Scene List" , "zbee_zcl_general.groups.scene_list" , FT_NONE , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_scenes_group_id , {
 "Group ID" , "zbee_zcl_general.scenes.group_id" , FT_UINT16 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_scenes_scene_id , {
 "Scene ID" , "zbee_zcl_general.scenes.scene_id" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_scenes_transit_time , {
 "Transition Time" , "zbee_zcl_general.scenes.transit_time" , FT_UINT16 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_scenes_status , {
 "Scenes Status" , "zbee_zcl_general.scenes.scenes_status" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_status_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_scenes_capacity , {
 "Scene Capacity" , "zbee_zcl_general.scenes.scene_capacity" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_scenes_scene_count , {
 "Scene Count" , "zbee_zcl_general.scenes.scene_count" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_scenes_attr_id_name_support , {
 "Scene Name Support" , "zbee_zcl_general.scenes.attr.name_support" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_scenes_group_names_support_values ) , ZBEE_ZCL_CMD_ID_SCENES_NAME_SUPPORT_MASK , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_scenes_attr_id_scene_valid , {
 "Scene Validity" , "zbee_zcl_general.scenes.scene_valid" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , ZBEE_ZCL_CMD_ID_SCENES_SUPPORTED_MASK , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_scenes_attr_str_len , {
 "Length" , "zbee_zcl_general.scenes.attr_str_len" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_scenes_attr_str , {
 "String" , "zbee_zcl_general.scenes.attr_str" , FT_STRING , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_scenes_extension_set_field , {
 "Extension Set" , "zbee_zcl_general.scenes.extension_set" , FT_BYTES , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_scenes_srv_rx_cmd_id , {
 "Command" , "zbee_zcl_general.scenes.cmd.srv_rx.id" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_scenes_srv_rx_cmd_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_scenes_srv_tx_cmd_id , {
 "Command" , "zbee_zcl_general.scenes.cmd.srv_tx.id" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_scenes_srv_tx_cmd_names ) , 0x00 , NULL , HFILL }
 }
 }
 ;
 static gint * ett [ ZBEE_ZCL_SCENES_NUM_ETT ] ;
 ett [ 0 ] = & ett_zbee_zcl_scenes ;
 ett [ 1 ] = & ett_zbee_zcl_scenes_scene_ctrl ;
 proto_zbee_zcl_scenes = proto_register_protocol ( "ZigBee ZCL Scenes" , "ZCL Scenes" , ZBEE_PROTOABBREV_ZCL_SCENES ) ;
 proto_register_field_array ( proto_zbee_zcl_scenes , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 register_dissector ( ZBEE_PROTOABBREV_ZCL_SCENES , dissect_zbee_zcl_scenes , proto_zbee_zcl_scenes ) ;
 }