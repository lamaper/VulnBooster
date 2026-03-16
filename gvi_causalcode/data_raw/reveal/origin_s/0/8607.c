static guint32 dissect_netb_name_query ( tvbuff_t * tvb , packet_info * pinfo _U_ , int offset , proto_tree * tree ) {
 guint8 local_session_number = tvb_get_guint8 ( tvb , offset + NB_DATA2 ) ;
 if ( local_session_number == 0 ) {
 proto_tree_add_uint_format_value ( tree , hf_netb_local_session_no , tvb , offset + NB_DATA2 , 1 , local_session_number , "0 (FIND.NAME request)" ) ;
 }
 else {
 proto_tree_add_item ( tree , hf_netb_local_session_no , tvb , offset + NB_DATA2 , 1 , ENC_LITTLE_ENDIAN ) ;
 }
 nb_call_name_type ( tvb , offset , tree ) ;
 nb_resp_corrl ( tvb , offset , tree ) ;
 netbios_add_name ( "Query Name" , tvb , offset + NB_RECVER_NAME , tree ) ;
 if ( local_session_number != 0 ) {
 netbios_add_name ( "Sender's Name" , tvb , offset + NB_SENDER_NAME , tree ) ;
 }
 return 0 ;
 }