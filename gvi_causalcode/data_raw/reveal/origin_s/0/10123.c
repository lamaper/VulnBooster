void proto_register_zbee_zcl_poll_ctrl ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_zbee_zcl_poll_ctrl_attr_id , {
 "Attribute" , "zbee_zcl_general.poll.attr_id" , FT_UINT16 , BASE_HEX , VALS ( zbee_zcl_poll_ctrl_attr_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_poll_ctrl_srv_rx_cmd_id , {
 "Command" , "zbee_zcl_general.poll.cmd.srv_rx.id" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_poll_ctrl_srv_rx_cmd_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_poll_ctrl_srv_tx_cmd_id , {
 "Command" , "zbee_zcl_general.poll.cmd.srv_tx.id" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_poll_ctrl_srv_tx_cmd_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_poll_ctrl_start_fast_polling , {
 "Start Fast Polling" , "zbee_zcl_general.poll.start" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_poll_ctrl_fast_poll_timeout , {
 "Fast Poll Timeout (quarterseconds)" , "zbee_zcl_general.poll.fast_timeout" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_poll_ctrl_new_long_poll_interval , {
 "New Long Poll Interval" , "zbee_zcl_general.poll.new_long_interval" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_poll_ctrl_new_short_poll_interval , {
 "New Short Poll Interval" , "zbee_zcl_general.poll.new_short_interval" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 }
 ;
 static gint * ett [ ZBEE_ZCL_POLL_CTRL_NUM_ETT ] ;
 ett [ 0 ] = & ett_zbee_zcl_poll_ctrl ;
 proto_zbee_zcl_poll_ctrl = proto_register_protocol ( "ZigBee ZCL Poll Control" , "ZCL Poll Control" , ZBEE_PROTOABBREV_ZCL_POLL ) ;
 proto_register_field_array ( proto_zbee_zcl_poll_ctrl , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 register_dissector ( ZBEE_PROTOABBREV_ZCL_POLL , dissect_zbee_zcl_poll_ctrl , proto_zbee_zcl_poll_ctrl ) ;
 }