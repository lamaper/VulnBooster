static int dissect_zbee_zcl_ota ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 proto_tree * payload_tree ;
 zbee_zcl_packet * zcl ;
 guint offset = 0 ;
 guint8 cmd_id ;
 gint rem_len ;
 if ( data == NULL ) return 0 ;
 zcl = ( zbee_zcl_packet * ) data ;
 cmd_id = zcl -> cmd_id ;
 if ( zcl -> direction == ZBEE_ZCL_FCF_TO_SERVER ) {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "%s, Seq: %u" , val_to_str_const ( cmd_id , zbee_zcl_ota_srv_rx_cmd_names , "Unknown Command" ) , zcl -> tran_seqno ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_srv_rx_cmd_id , tvb , offset , 1 , cmd_id ) ;
 rem_len = tvb_reported_length_remaining ( tvb , ++ offset ) ;
 if ( rem_len > 0 ) {
 payload_tree = proto_tree_add_subtree ( tree , tvb , offset , rem_len , ett_zbee_zcl_ota , NULL , "Payload" ) ;
 switch ( cmd_id ) {
 case ZBEE_ZCL_CMD_ID_OTA_QUERY_NEXT_IMAGE_REQ : dissect_zcl_ota_querynextimagereq ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_OTA_IMAGE_BLOCK_REQ : dissect_zcl_ota_imageblockreq ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_OTA_IMAGE_PAGE_REQ : dissect_zcl_ota_imagepagereq ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_OTA_UPGRADE_END_REQ : dissect_zcl_ota_upgradeendreq ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_OTA_QUERY_SPEC_FILE_REQ : dissect_zcl_ota_queryspecfilereq ( tvb , payload_tree , & offset ) ;
 break ;
 default : break ;
 }
 }
 }
 else {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "%s, Seq: %u" , val_to_str_const ( cmd_id , zbee_zcl_ota_srv_tx_cmd_names , "Unknown Command" ) , zcl -> tran_seqno ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_srv_tx_cmd_id , tvb , offset , 1 , cmd_id ) ;
 rem_len = tvb_reported_length_remaining ( tvb , ++ offset ) ;
 if ( rem_len > 0 ) {
 payload_tree = proto_tree_add_subtree ( tree , tvb , offset , rem_len , ett_zbee_zcl_ota , NULL , "Payload" ) ;
 switch ( cmd_id ) {
 case ZBEE_ZCL_CMD_ID_OTA_IMAGE_NOTIFY : dissect_zcl_ota_imagenotify ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_OTA_QUERY_NEXT_IMAGE_RSP : dissect_zcl_ota_querynextimagersp ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_OTA_IMAGE_BLOCK_RSP : dissect_zcl_ota_imageblockrsp ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_OTA_UPGRADE_END_RSP : dissect_zcl_ota_upgradeendrsp ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_OTA_QUERY_SPEC_FILE_RSP : dissect_zcl_ota_queryspecfilersp ( tvb , payload_tree , & offset ) ;
 break ;
 default : break ;
 }
 }
 }
 return tvb_captured_length ( tvb ) ;
 }