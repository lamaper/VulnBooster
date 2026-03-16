static int dissect_CPMSendNotifyOut ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * parent_tree , gboolean in _U_ , void * data _U_ ) {
 gint offset = 16 ;
 proto_item * item ;
 proto_tree * tree ;
 col_append_str ( pinfo -> cinfo , COL_INFO , "SendNotify" ) ;
 item = proto_tree_add_item ( parent_tree , hf_mswsp_msg , tvb , offset , - 1 , ENC_NA ) ;
 tree = proto_item_add_subtree ( item , ett_mswsp_msg ) ;
 proto_item_set_text ( item , "GetSendNotifyOut" ) ;
 proto_tree_add_item ( tree , hf_mswsp_msg_cpmsendnotify_watchnotify , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 return tvb_reported_length ( tvb ) ;
 }