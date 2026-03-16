static guint32 dissect_netb_name_resp ( tvbuff_t * tvb , packet_info * pinfo _U_ , int offset , proto_tree * tree ) {
 guint8 local_session_number = tvb_get_guint8 ( tvb , offset + NB_DATA2 ) ;
 switch ( local_session_number ) {
 case 0x00 : proto_tree_add_uint_format_value ( tree , hf_netb_state_of_name , tvb , offset + NB_DATA2 , 1 , local_session_number , "No LISTEN pending, or FIND.NAME response" ) ;
 break ;
 case 0xFF : proto_tree_add_uint_format_value ( tree , hf_netb_state_of_name , tvb , offset + NB_DATA2 , 1 , local_session_number , "LISTEN pending, but insufficient resources to establish session" ) ;
 break ;
 default : proto_tree_add_item ( tree , hf_netb_local_session_no , tvb , offset + NB_DATA2 , 1 , ENC_LITTLE_ENDIAN ) ;
 break ;
 }
 nb_call_name_type ( tvb , offset , tree ) ;
 nb_xmit_corrl ( tvb , offset , tree ) ;
 if ( local_session_number != 0x00 && local_session_number != 0xFF ) nb_resp_corrl ( tvb , offset , tree ) ;
 netbios_add_name ( "Receiver's Name" , tvb , offset + NB_RECVER_NAME , tree ) ;
 if ( local_session_number != 0x00 && local_session_number != 0xFF ) {
 netbios_add_name ( "Sender's Name" , tvb , offset + NB_SENDER_NAME , tree ) ;
 }
 return 0 ;
 }