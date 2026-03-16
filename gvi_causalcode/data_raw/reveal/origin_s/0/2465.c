static guint32 dissect_netb_status_query ( tvbuff_t * tvb , packet_info * pinfo _U_ , int offset , proto_tree * tree ) {
 guint8 status_request = tvb_get_guint8 ( tvb , offset + NB_DATA1 ) ;
 switch ( status_request ) {
 case 0 : proto_tree_add_uint_format_value ( tree , hf_netb_status_request , tvb , offset + NB_DATA1 , 1 , status_request , "NetBIOS 1.x or 2.0" ) ;
 break ;
 case 1 : proto_tree_add_uint_format_value ( tree , hf_netb_status_request , tvb , offset + NB_DATA1 , 1 , status_request , "NetBIOS 2.1, initial status request" ) ;
 break ;
 default : proto_tree_add_uint_format_value ( tree , hf_netb_status_request , tvb , offset + NB_DATA1 , 1 , status_request , "NetBIOS 2.1, %u names received so far" , status_request ) ;
 break ;
 }
 nb_data2 ( hf_netb_status_buffer_len , tvb , offset , tree ) ;
 nb_resp_corrl ( tvb , offset , tree ) ;
 netbios_add_name ( "Receiver's Name" , tvb , offset + NB_RECVER_NAME , tree ) ;
 netbios_add_name ( "Sender's Name" , tvb , offset + NB_SENDER_NAME , tree ) ;
 return 0 ;
 }