static int dissect_zbee_zcl_poll_ctrl ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 zbee_zcl_packet * zcl ;
 guint offset = 0 ;
 guint8 cmd_id ;
 if ( data == NULL ) return 0 ;
 zcl = ( zbee_zcl_packet * ) data ;
 cmd_id = zcl -> cmd_id ;
 if ( zcl -> direction == ZBEE_ZCL_FCF_TO_SERVER ) {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "%s, Seq: %u" , val_to_str_const ( cmd_id , zbee_zcl_poll_ctrl_srv_rx_cmd_names , "Unknown Command" ) , zcl -> tran_seqno ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_poll_ctrl_srv_rx_cmd_id , tvb , offset , 1 , cmd_id ) ;
 offset ++ ;
 switch ( cmd_id ) {
 case ZBEE_ZCL_CMD_ID_POLL_CTRL_CHECK_IN_RESPONSE : proto_tree_add_item ( tree , hf_zbee_zcl_poll_ctrl_start_fast_polling , tvb , offset , 1 , ENC_NA ) ;
 offset ++ ;
 proto_tree_add_item ( tree , hf_zbee_zcl_poll_ctrl_fast_poll_timeout , tvb , offset , 2 , ENC_LITTLE_ENDIAN ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_POLL_CTRL_FAST_POLL_STOP : break ;
 case ZBEE_ZCL_CMD_ID_POLL_CTRL_SET_LONG_POLL : proto_tree_add_item ( tree , hf_zbee_zcl_poll_ctrl_new_long_poll_interval , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_POLL_CTRL_SET_SHORT_POLL : proto_tree_add_item ( tree , hf_zbee_zcl_poll_ctrl_new_short_poll_interval , tvb , offset , 2 , ENC_LITTLE_ENDIAN ) ;
 break ;
 default : break ;
 }
 }
 else {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "%s, Seq: %u" , val_to_str_const ( cmd_id , zbee_zcl_poll_ctrl_srv_tx_cmd_names , "Unknown Command" ) , zcl -> tran_seqno ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_poll_ctrl_srv_tx_cmd_id , tvb , offset , 1 , ENC_NA ) ;
 offset ++ ;
 switch ( cmd_id ) {
 case ZBEE_ZCL_CMD_ID_POLL_CTRL_CHECK_IN : default : break ;
 }
 }
 return tvb_captured_length ( tvb ) ;
 }