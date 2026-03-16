void proto_register_zbee_zcl_part ( void ) {
 guint8 i , j ;
 static hf_register_info hf [ ] = {
 {
 & hf_zbee_zcl_part_attr_id , {
 "Attribute" , "zbee_zcl_general.part.attr_id" , FT_UINT16 , BASE_HEX , VALS ( zbee_zcl_part_attr_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_part_srv_tx_cmd_id , {
 "Command" , "zbee_zcl_general.part.cmd.srv_tx.id" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_part_srv_tx_cmd_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_part_srv_rx_cmd_id , {
 "Command" , "zbee_zcl_general.part.cmd.srv_rx.id" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_part_srv_rx_cmd_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_part_opt , {
 "Fragmentation Options" , "zbee_zcl_general.part.opt" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_part_opt_first_block , {
 "First Block" , "zbee_zcl_general.part.opt.first_block" , FT_UINT8 , BASE_HEX , NULL , ZBEE_ZCL_PART_OPT_1_BLOCK , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_part_opt_indic_len , {
 "Indicator length" , "zbee_zcl_general.part.opt.indic_len" , FT_UINT8 , BASE_DEC , VALS ( zbee_zcl_part_id_length_names ) , ZBEE_ZCL_PART_OPT_INDIC_LEN , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_part_opt_res , {
 "Reserved" , "zbee_zcl_general.part.opt.res" , FT_UINT8 , BASE_HEX , NULL , ZBEE_ZCL_PART_OPT_RESERVED , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_part_first_frame_id , {
 "First Frame ID" , "zbee_zcl_general.part.first_frame_id" , FT_UINT16 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_part_part_indicator , {
 "Partition Indicator" , "zbee_zcl_general.part.part_indicator" , FT_UINT16 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_part_part_frame_len , {
 "Partition Frame Length" , "zbee_zcl_general.part.part_frame_length" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_part_part_frame , {
 "Partition Frame" , "zbee_zcl_general.part.part_frame" , FT_BYTES , SEP_COLON , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_part_partitioned_cluster_id , {
 "Partitioned Cluster ID" , "zbee_zcl_general.part.part_cluster_id" , FT_UINT16 , BASE_HEX , VALS ( zbee_aps_cid_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_part_ack_opt , {
 "Ack Options" , "zbee_zcl_general.ack_opt.part" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_part_ack_opt_nack_id_len , {
 "Nack Id Length" , "zbee_zcl_general.ack_opt.part.nack_id.len" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_part_id_length_names ) , ZBEE_ZCL_PART_ACK_OPT_NACK_LEN , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_part_ack_opt_res , {
 "Reserved" , "zbee_zcl_general.part.ack_opt.reserved" , FT_UINT8 , BASE_HEX , NULL , ZBEE_ZCL_PART_ACK_OPT_RESERVED , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_part_nack_id , {
 "Nack Id" , "zbee_zcl_general.part.nack_id" , FT_UINT16 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 }
 ;
 gint * ett [ ZBEE_ZCL_PART_NUM_ETT ] ;
 ett [ 0 ] = & ett_zbee_zcl_part ;
 ett [ 1 ] = & ett_zbee_zcl_part_fragm_options ;
 ett [ 2 ] = & ett_zbee_zcl_part_ack_opts ;
 for ( i = 0 , j = ZBEE_ZCL_PART_NUM_GENERIC_ETT ;
 i < ZBEE_ZCL_PART_NUM_NACK_ID_ETT ;
 i ++ , j ++ ) {
 ett_zbee_zcl_part_nack_id_list [ i ] = - 1 ;
 ett [ j ] = & ett_zbee_zcl_part_nack_id_list [ i ] ;
 }
 for ( i = 0 ;
 i < ZBEE_ZCL_PART_NUM_ATTRS_ID_ETT ;
 i ++ , j ++ ) {
 ett_zbee_zcl_part_attrs_id_list [ i ] = - 1 ;
 ett [ j ] = & ett_zbee_zcl_part_attrs_id_list [ i ] ;
 }
 proto_zbee_zcl_part = proto_register_protocol ( "ZigBee ZCL Partition" , "ZCL Partition" , ZBEE_PROTOABBREV_ZCL_PART ) ;
 proto_register_field_array ( proto_zbee_zcl_part , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 register_dissector ( ZBEE_PROTOABBREV_ZCL_PART , dissect_zbee_zcl_part , proto_zbee_zcl_part ) ;
 }