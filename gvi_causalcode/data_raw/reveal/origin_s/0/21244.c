static int dissect_zbee_zcl_pwr_prof ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 proto_tree * payload_tree ;
 zbee_zcl_packet * zcl ;
 guint offset = 0 ;
 guint8 cmd_id ;
 gint rem_len ;
 if ( data == NULL ) return 0 ;
 zcl = ( zbee_zcl_packet * ) data ;
 cmd_id = zcl -> cmd_id ;
 if ( zcl -> direction == ZBEE_ZCL_FCF_TO_SERVER ) {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "%s, Seq: %u" , val_to_str_const ( cmd_id , zbee_zcl_pwr_prof_srv_rx_cmd_names , "Unknown Command" ) , zcl -> tran_seqno ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_pwr_prof_srv_rx_cmd_id , tvb , offset , 1 , cmd_id ) ;
 rem_len = tvb_reported_length_remaining ( tvb , ++ offset ) ;
 if ( rem_len > 0 ) {
 payload_tree = proto_tree_add_subtree ( tree , tvb , offset , rem_len , ett_zbee_zcl_pwr_prof , NULL , "Payload" ) ;
 switch ( cmd_id ) {
 case ZBEE_ZCL_CMD_ID_PWR_PROF_PWR_PROF_REQ : case ZBEE_ZCL_CMD_ID_PWR_PROF_PWR_PROF_SCHED_CONSTRS_REQ : case ZBEE_ZCL_CMD_ID_PWR_PROF_ENERGY_PHASES_SCHED_STATE_REQ : dissect_zcl_pwr_prof_pwrprofreq ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_PWR_PROF_PWR_PROF_STATE_REQ : break ;
 case ZBEE_ZCL_CMD_ID_PWR_PROF_GET_PWR_PROF_PRICE_RSP : case ZBEE_ZCL_CMD_ID_PWR_PROF_GET_PWR_PROF_PRICE_EXT_RSP : dissect_zcl_pwr_prof_getpwrprofpricersp ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_PWR_PROF_GET_OVERALL_SCHED_PRICE_RSP : dissect_zcl_pwr_prof_getoverallschedpricersp ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_PWR_PROF_ENERGY_PHASES_SCHED_NOTIF : case ZBEE_ZCL_CMD_ID_PWR_PROF_ENERGY_PHASES_SCHED_RSP : dissect_zcl_pwr_prof_enphsschednotif ( tvb , payload_tree , & offset ) ;
 break ;
 default : break ;
 }
 }
 }
 else {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "%s, Seq: %u" , val_to_str_const ( cmd_id , zbee_zcl_pwr_prof_srv_tx_cmd_names , "Unknown Command" ) , zcl -> tran_seqno ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_pwr_prof_srv_tx_cmd_id , tvb , offset , 1 , cmd_id ) ;
 rem_len = tvb_reported_length_remaining ( tvb , ++ offset ) ;
 if ( rem_len > 0 ) {
 payload_tree = proto_tree_add_subtree ( tree , tvb , offset , rem_len , ett_zbee_zcl_pwr_prof , NULL , "Payload" ) ;
 switch ( cmd_id ) {
 case ZBEE_ZCL_CMD_ID_PWR_PROF_PWR_PROF_NOTIF : case ZBEE_ZCL_CMD_ID_PWR_PROF_PWR_PROF_RSP : dissect_zcl_pwr_prof_pwrprofnotif ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_PWR_PROF_PWR_PROF_STATE_RSP : case ZBEE_ZCL_CMD_ID_PWR_PROF_PWR_PROF_STATE_NOTIF : dissect_zcl_pwr_prof_pwrprofstatersp ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_PWR_PROF_GET_OVERALL_SCHED_PRICE : break ;
 case ZBEE_ZCL_CMD_ID_PWR_PROF_ENERGY_PHASES_SCHED_STATE_RSP : case ZBEE_ZCL_CMD_ID_PWR_PROF_ENERGY_PHASES_SCHED_STATE_NOITIF : dissect_zcl_pwr_prof_enphsschednotif ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_PWR_PROF_GET_PWR_PROF_PRICE : case ZBEE_ZCL_CMD_ID_PWR_PROF_ENERGY_PHASES_SCHED_REQ : dissect_zcl_pwr_prof_pwrprofreq ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_PWR_PROF_PWR_PROF_SCHED_CONSTRS_NOTIF : case ZBEE_ZCL_CMD_ID_PWR_PROF_PWR_PROF_SCHED_CONSTRS_RSP : dissect_zcl_pwr_prof_pwrprofschedcontrsnotif ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_PWR_PROF_GET_PWR_PROF_PRICE_EXT : dissect_zcl_pwr_prof_pwrprofpriceext ( tvb , payload_tree , & offset ) ;
 break ;
 default : break ;
 }
 }
 }
 return tvb_captured_length ( tvb ) ;
 }