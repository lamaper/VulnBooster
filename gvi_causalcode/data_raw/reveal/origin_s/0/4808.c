static int dissect_zbee_zcl_scenes ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 proto_tree * payload_tree ;
 zbee_zcl_packet * zcl ;
 guint offset = 0 ;
 guint8 cmd_id ;
 gint rem_len ;
 if ( data == NULL ) return 0 ;
 zcl = ( zbee_zcl_packet * ) data ;
 cmd_id = zcl -> cmd_id ;
 if ( zcl -> direction == ZBEE_ZCL_FCF_TO_SERVER ) {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "%s, Seq: %u" , val_to_str_const ( cmd_id , zbee_zcl_scenes_srv_rx_cmd_names , "Unknown Command" ) , zcl -> tran_seqno ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_scenes_srv_rx_cmd_id , tvb , offset , 1 , cmd_id ) ;
 rem_len = tvb_reported_length_remaining ( tvb , ++ offset ) ;
 if ( rem_len > 0 ) {
 payload_tree = proto_tree_add_subtree ( tree , tvb , offset , rem_len , ett_zbee_zcl_scenes , NULL , "Payload" ) ;
 switch ( cmd_id ) {
 case ZBEE_ZCL_CMD_ID_SCENES_ADD_SCENE : dissect_zcl_scenes_add_scene ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_SCENES_VIEW_SCENE : case ZBEE_ZCL_CMD_ID_SCENES_REMOVE_SCENE : case ZBEE_ZCL_CMD_ID_SCENES_STORE_SCENE : case ZBEE_ZCL_CMD_ID_SCENES_RECALL_SCENE : dissect_zcl_scenes_view_remove_store_recall_scene ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_SCENES_REMOVE_ALL_SCENES : case ZBEE_ZCL_CMD_ID_SCENES_GET_SCENE_MEMBERSHIP : dissect_zcl_scenes_remove_all_get_scene_membership ( tvb , payload_tree , & offset ) ;
 break ;
 default : break ;
 }
 }
 }
 else {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "%s, Seq: %u" , val_to_str_const ( cmd_id , zbee_zcl_scenes_srv_tx_cmd_names , "Unknown Command" ) , zcl -> tran_seqno ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_scenes_srv_tx_cmd_id , tvb , offset , 1 , cmd_id ) ;
 rem_len = tvb_reported_length_remaining ( tvb , ++ offset ) ;
 if ( rem_len > 0 ) {
 payload_tree = proto_tree_add_subtree ( tree , tvb , offset , rem_len , ett_zbee_zcl_scenes , NULL , "Payload" ) ;
 switch ( cmd_id ) {
 case ZBEE_ZCL_CMD_ID_SCENES_ADD_SCENE_RESPONSE : case ZBEE_ZCL_CMD_ID_SCENES_REMOVE_SCENE_RESPONSE : case ZBEE_ZCL_CMD_ID_SCENES_STORE_SCENE_RESPONSE : dissect_zcl_scenes_add_remove_store_scene_response ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_SCENES_VIEW_SCENE_RESPONSE : dissect_zcl_scenes_view_scene_response ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_SCENES_REMOVE_ALL_SCENES_RESPONSE : dissect_zcl_scenes_remove_all_scenes_response ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_SCENES_GET_SCENE_MEMBERSHIP_RESPONSE : dissect_zcl_scenes_get_scene_membership_response ( tvb , payload_tree , & offset ) ;
 break ;
 default : break ;
 }
 }
 }
 return tvb_captured_length ( tvb ) ;
 }