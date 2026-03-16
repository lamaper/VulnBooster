void proto_register_zbee_zcl_appl_evtalt ( void ) {
 guint i , j ;
 static hf_register_info hf [ ] = {
 {
 & hf_zbee_zcl_appl_evtalt_srv_tx_cmd_id , {
 "Command" , "zbee_zcl_ha.applevtalt.cmd.srv_tx.id" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_appl_evtalt_srv_tx_cmd_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_evtalt_srv_rx_cmd_id , {
 "Command" , "zbee_zcl_ha.applevtalt.cmd.srv_rx.id" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_appl_evtalt_srv_rx_cmd_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_evtalt_count_num , {
 "Number of Alerts" , "zbee_zcl_ha.applevtalt.count.num" , FT_UINT8 , BASE_DEC , NULL , ZBEE_ZCL_APPL_EVTALT_COUNT_NUM_MASK , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_evtalt_count_type , {
 "Type of Alerts" , "zbee_zcl_ha.applevtalt.count.type" , FT_UINT8 , BASE_DEC , NULL , ZBEE_ZCL_APPL_EVTALT_COUNT_TYPE_MASK , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_evtalt_alert_id , {
 "Alert Id" , "zbee_zcl_ha.applevtalt.alert_id" , FT_UINT24 , BASE_HEX , NULL , ZBEE_ZCL_APPL_EVTALT_ALERT_ID_MASK , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_evtalt_category , {
 "Category" , "zbee_zcl_ha.applevtalt.category" , FT_UINT24 , BASE_HEX , VALS ( zbee_zcl_appl_evtalt_category_names ) , ZBEE_ZCL_APPL_EVTALT_CATEGORY_MASK , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_evtalt_status , {
 "Status" , "zbee_zcl_ha.applevtalt.status" , FT_UINT24 , BASE_HEX , VALS ( zbee_zcl_appl_evtalt_status_names ) , ZBEE_ZCL_APPL_EVTALT_STATUS_MASK , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_evtalt_reserved , {
 "Reserved" , "zbee_zcl_ha.applevtalt.reserved" , FT_UINT24 , BASE_HEX , NULL , ZBEE_ZCL_APPL_EVTALT_RESERVED_MASK , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_evtalt_proprietary , {
 "Proprietary" , "zbee_zcl_ha.applevtalt.proprietary" , FT_UINT24 , BASE_HEX , NULL , ZBEE_ZCL_APPL_EVTALT_PROPRIETARY_MASK , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_evtalt_event_hdr , {
 "Event Header" , "zbee_zcl_ha.applevtalt.event.header" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_evtalt_event_id , {
 "Event Id" , "zbee_zcl_ha.applevtalt.event.id" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_appl_evtalt_event_id_names ) , 0x00 , NULL , HFILL }
 }
 }
 ;
 gint * ett [ ZBEE_ZCL_APPL_EVTALT_NUM_ETT ] ;
 ett [ 0 ] = & ett_zbee_zcl_appl_evtalt ;
 for ( i = 0 , j = ZBEE_ZCL_APPL_EVTALT_NUM_GENERIC_ETT ;
 i < ZBEE_ZCL_APPL_EVTALT_NUM_STRUCT_ETT ;
 i ++ , j ++ ) {
 ett_zbee_zcl_appl_evtalt_alerts_struct [ i ] = - 1 ;
 ett [ j ] = & ett_zbee_zcl_appl_evtalt_alerts_struct [ i ] ;
 }
 proto_zbee_zcl_appl_evtalt = proto_register_protocol ( "ZigBee ZCL Appliance Events & Alert" , "ZCL Appliance Events & Alert" , ZBEE_PROTOABBREV_ZCL_APPLEVTALT ) ;
 proto_register_field_array ( proto_zbee_zcl_appl_evtalt , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 register_dissector ( ZBEE_PROTOABBREV_ZCL_APPLEVTALT , dissect_zbee_zcl_appl_evtalt , proto_zbee_zcl_appl_evtalt ) ;
 }