void proto_register_zbee_zcl_appl_stats ( void ) {
 guint i , j ;
 static hf_register_info hf [ ] = {
 {
 & hf_zbee_zcl_appl_stats_attr_id , {
 "Attribute" , "zbee_zcl_ha.applstats.attr_id" , FT_UINT16 , BASE_HEX , VALS ( zbee_zcl_appl_stats_attr_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_stats_srv_tx_cmd_id , {
 "Command" , "zbee_zcl_ha.applstats.cmd.srv_tx.id" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_appl_stats_srv_tx_cmd_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_stats_srv_rx_cmd_id , {
 "Command" , "zbee_zcl_ha.applstats.cmd.srv_rx.id" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_appl_stats_srv_rx_cmd_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_stats_utc_time , {
 "UTC Time" , "zbee_zcl_ha.applstats.utc_time" , FT_UINT32 , BASE_CUSTOM , CF_FUNC ( decode_zcl_appl_stats_utc_time ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_stats_log_length , {
 "Log Length" , "zbee_zcl_ha.applstats.log.length" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_stats_log_id , {
 "Log ID" , "zbee_zcl_ha.applstats.log.id" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_stats_log_queue_size , {
 "Log Queue Size" , "zbee_zcl_ha.applstats.log_queue_size" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_stats_log_payload , {
 "Log Payload" , "zbee_zcl_ha.applstats.log.payload" , FT_BYTES , SEP_COLON , NULL , 0x00 , NULL , HFILL }
 }
 , }
 ;
 static gint * ett [ ZBEE_ZCL_APPL_STATS_NUM_ETT ] ;
 ett [ 0 ] = & ett_zbee_zcl_appl_stats ;
 for ( i = 0 , j = ZBEE_ZCL_APPL_STATS_NUM_GENERIC_ETT ;
 i < ZBEE_ZCL_APPL_STATS_NUM_LOGS_ETT ;
 i ++ , j ++ ) {
 ett_zbee_zcl_appl_stats_logs [ i ] = - 1 ;
 ett [ j ] = & ett_zbee_zcl_appl_stats_logs [ i ] ;
 }
 proto_zbee_zcl_appl_stats = proto_register_protocol ( "ZigBee ZCL Appliance Statistics" , "ZCL Appliance Statistics" , ZBEE_PROTOABBREV_ZCL_APPLSTATS ) ;
 proto_register_field_array ( proto_zbee_zcl_appl_stats , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 register_dissector ( ZBEE_PROTOABBREV_ZCL_APPLSTATS , dissect_zbee_zcl_appl_stats , proto_zbee_zcl_appl_stats ) ;
 }