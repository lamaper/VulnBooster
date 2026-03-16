static int dissect_h225_H323UserInformation ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data _U_ ) {
 proto_item * it ;
 proto_tree * tr ;
 int offset = 0 ;
 h225_packet_info * h225_pi ;
 h225_pi = create_h225_packet_info ( pinfo ) ;
 h225_pi -> msg_type = H225_CS ;
 p_add_proto_data ( wmem_packet_scope ( ) , pinfo , proto_h225 , 0 , h225_pi ) ;
 next_tvb_init ( & h245_list ) ;
 next_tvb_init ( & tp_list ) ;
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , PSNAME ) ;
 col_clear ( pinfo -> cinfo , COL_INFO ) ;
 it = proto_tree_add_protocol_format ( tree , proto_h225 , tvb , 0 , - 1 , PSNAME " CS" ) ;
 tr = proto_item_add_subtree ( it , ett_h225 ) ;
 offset = dissect_H323_UserInformation_PDU ( tvb , pinfo , tr , NULL ) ;
 if ( h245_list . count ) {
 col_append_str ( pinfo -> cinfo , COL_PROTOCOL , "/" ) ;
 col_set_fence ( pinfo -> cinfo , COL_PROTOCOL ) ;
 }
 next_tvb_call ( & h245_list , pinfo , tree , h245dg_handle , data_handle ) ;
 next_tvb_call ( & tp_list , pinfo , tree , NULL , data_handle ) ;
 tap_queue_packet ( h225_tap , pinfo , h225_pi ) ;
 return offset ;
 }