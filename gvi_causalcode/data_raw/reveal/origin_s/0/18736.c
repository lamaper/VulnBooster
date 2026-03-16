static guint32 dissect_netb_session_confirm ( tvbuff_t * tvb , packet_info * pinfo _U_ , int offset , proto_tree * tree ) {
 netbios_add_ses_confirm_flags ( tvb , tree , offset + NB_FLAGS ) ;
 nb_data2 ( hf_netb_max_data_recv_size , tvb , offset , tree ) ;
 nb_xmit_corrl ( tvb , offset , tree ) ;
 nb_resp_corrl ( tvb , offset , tree ) ;
 nb_remote_session ( tvb , offset , tree ) ;
 nb_local_session ( tvb , offset , tree ) ;
 return 0 ;
 }