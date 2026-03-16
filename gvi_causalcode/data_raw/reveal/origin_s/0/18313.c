static int dissect_zbee_zcl_color_control ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 proto_tree * payload_tree ;
 zbee_zcl_packet * zcl ;
 guint offset = 0 ;
 guint8 cmd_id ;
 gint rem_len ;
 if ( data == NULL ) return 0 ;
 zcl = ( zbee_zcl_packet * ) data ;
 cmd_id = zcl -> cmd_id ;
 if ( zcl -> direction == ZBEE_ZCL_FCF_TO_SERVER ) {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "%s, Seq: %u" , val_to_str_const ( cmd_id , zbee_zcl_color_control_srv_rx_cmd_names , "Unknown Command" ) , zcl -> tran_seqno ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_color_control_srv_rx_cmd_id , tvb , offset , 1 , cmd_id ) ;
 rem_len = tvb_reported_length_remaining ( tvb , ++ offset ) ;
 if ( rem_len > 0 ) {
 payload_tree = proto_tree_add_subtree ( tree , tvb , offset , rem_len , ett_zbee_zcl_color_control , NULL , "Payload" ) ;
 switch ( cmd_id ) {
 case ZBEE_ZCL_CMD_ID_COLOR_CONTROL_MOVE_TO_HUE : dissect_zcl_color_control_move_to_hue ( tvb , payload_tree , & offset , ZBEE_ZCL_NORMAL_HUE ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_COLOR_CONTROL_MOVE_HUE : dissect_zcl_color_control_move_hue_saturation ( tvb , payload_tree , & offset , ZBEE_ZCL_NORMAL_HUE ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_COLOR_CONTROL_STEP_HUE : dissect_zcl_color_control_step_hue_saturation ( tvb , payload_tree , & offset , ZBEE_ZCL_NORMAL_HUE ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_COLOR_CONTROL_MOVE_TO_SATURATION : dissect_zcl_color_control_move_to_saturation ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_COLOR_CONTROL_MOVE_SATURATION : dissect_zcl_color_control_move_hue_saturation ( tvb , payload_tree , & offset , ZBEE_ZCL_NORMAL_HUE ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_COLOR_CONTROL_STEP_SATURATION : dissect_zcl_color_control_step_hue_saturation ( tvb , payload_tree , & offset , ZBEE_ZCL_NORMAL_HUE ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_COLOR_CONTROL_MOVE_TO_HUE_AND_SATURATION : dissect_zcl_color_control_move_to_hue_and_saturation ( tvb , payload_tree , & offset , ZBEE_ZCL_NORMAL_HUE ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_COLOR_CONTROL_MOVE_TO_COLOR : dissect_zcl_color_control_move_to_color ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_COLOR_CONTROL_MOVE_COLOR : dissect_zcl_color_control_move_color ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_COLOR_CONTROL_STEP_COLOR : dissect_zcl_color_control_step_color ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_COLOR_CONTROL_MOVE_TO_COLOR_TEMP : dissect_zcl_color_control_move_to_color_temp ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_COLOR_CONTROL_ENHANCED_MOVE_TO_HUE : dissect_zcl_color_control_move_to_hue ( tvb , payload_tree , & offset , ZBEE_ZCL_ENHANCED_HUE ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_COLOR_CONTROL_ENHANCED_MOVE_HUE : dissect_zcl_color_control_move_hue_saturation ( tvb , payload_tree , & offset , ZBEE_ZCL_ENHANCED_HUE ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_COLOR_CONTROL_ENHANCED_STEP_HUE : dissect_zcl_color_control_step_hue_saturation ( tvb , payload_tree , & offset , ZBEE_ZCL_ENHANCED_HUE ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_COLOR_CONTROL_ENHANCED_MOVE_TO_HUE_AND_SATURATION : dissect_zcl_color_control_move_to_hue_and_saturation ( tvb , payload_tree , & offset , ZBEE_ZCL_ENHANCED_HUE ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_COLOR_CONTROL_COLOR_LOOP_SET : dissect_zcl_color_control_color_loop_set ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_COLOR_CONTROL_MOVE_COLOR_TEMP : dissect_zcl_color_control_move_color_temp ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_COLOR_CONTROL_STEP_COLOR_TEMP : dissect_zcl_color_control_step_color_temp ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_COLOR_CONTROL_STOP_MOVE_STEP : default : break ;
 }
 }
 }
 return tvb_captured_length ( tvb ) ;
 }