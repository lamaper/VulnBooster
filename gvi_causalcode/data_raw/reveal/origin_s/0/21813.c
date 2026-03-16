static int dissect_zbee_zcl_appl_stats ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 proto_tree * payload_tree ;
 zbee_zcl_packet * zcl ;
 guint offset = 0 ;
 guint8 cmd_id ;
 gint rem_len ;
 if ( data == NULL ) return 0 ;
 zcl = ( zbee_zcl_packet * ) data ;
 cmd_id = zcl -> cmd_id ;
 if ( zcl -> direction == ZBEE_ZCL_FCF_TO_SERVER ) {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "%s, Seq: %u" , val_to_str_const ( cmd_id , zbee_zcl_appl_stats_srv_rx_cmd_names , "Unknown Command" ) , zcl -> tran_seqno ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_appl_stats_srv_rx_cmd_id , tvb , offset , 1 , cmd_id ) ;
 rem_len = tvb_reported_length_remaining ( tvb , ++ offset ) ;
 if ( rem_len > 0 ) {
 payload_tree = proto_tree_add_subtree ( tree , tvb , offset , rem_len , ett_zbee_zcl_appl_stats , NULL , "Payload" ) ;
 switch ( cmd_id ) {
 case ZBEE_ZCL_CMD_ID_APPL_STATS_LOG_REQ : dissect_zcl_appl_stats_log_req ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_APPL_STATS_LOG_QUEUE_REQ : break ;
 default : break ;
 }
 }
 }
 else {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "%s, Seq: %u" , val_to_str_const ( cmd_id , zbee_zcl_appl_stats_srv_tx_cmd_names , "Unknown Command" ) , zcl -> tran_seqno ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_appl_stats_srv_tx_cmd_id , tvb , offset , 1 , cmd_id ) ;
 rem_len = tvb_reported_length_remaining ( tvb , ++ offset ) ;
 if ( rem_len > 0 ) {
 payload_tree = proto_tree_add_subtree ( tree , tvb , offset , rem_len , ett_zbee_zcl_appl_stats , NULL , "Payload" ) ;
 switch ( cmd_id ) {
 case ZBEE_ZCL_CMD_ID_APPL_STATS_LOG_NOTIF : case ZBEE_ZCL_CMD_ID_APPL_STATS_LOG_RSP : dissect_zcl_appl_stats_log_rsp ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_APPL_STATS_LOG_QUEUE_RSP : case ZBEE_ZCL_CMD_ID_APPL_STATS_STATS_AVAILABLE : dissect_zcl_appl_stats_log_queue_rsp ( tvb , payload_tree , & offset ) ;
 break ;
 default : break ;
 }
 }
 }
 return tvb_captured_length ( tvb ) ;
 }