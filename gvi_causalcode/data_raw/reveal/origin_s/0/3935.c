static int dissect_zbee_zcl_basic ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 zbee_zcl_packet * zcl ;
 guint offset = 0 ;
 guint8 cmd_id ;
 if ( data == NULL ) return 0 ;
 zcl = ( zbee_zcl_packet * ) data ;
 cmd_id = zcl -> cmd_id ;
 if ( zcl -> direction == ZBEE_ZCL_FCF_TO_SERVER ) {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "%s, Seq: %u" , val_to_str_const ( cmd_id , zbee_zcl_basic_srv_rx_cmd_names , "Unknown Command" ) , zcl -> tran_seqno ) ;
 if ( tree ) {
 proto_tree_add_item ( tree , hf_zbee_zcl_basic_srv_rx_cmd_id , tvb , offset , 1 , cmd_id ) ;
 }
 switch ( cmd_id ) {
 case ZBEE_ZCL_CMD_ID_BASIC_RESET_FACTORY_DEFAULTS : break ;
 default : break ;
 }
 }
 return tvb_captured_length ( tvb ) ;
 }