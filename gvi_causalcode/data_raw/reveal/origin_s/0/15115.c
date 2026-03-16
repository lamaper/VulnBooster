static guint32 dissect_netb_add_name_resp ( tvbuff_t * tvb , packet_info * pinfo _U_ , int offset , proto_tree * tree ) {
 nb_data1 ( hf_netb_status , tvb , offset , tree ) ;
 nb_data2 ( hf_netb_name_type , tvb , offset , tree ) ;
 nb_xmit_corrl ( tvb , offset , tree ) ;
 netbios_add_name ( "Name to be added" , tvb , offset + NB_RECVER_NAME , tree ) ;
 netbios_add_name ( "Name to be added" , tvb , offset + NB_SENDER_NAME , tree ) ;
 return 0 ;
 }