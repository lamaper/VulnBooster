static guint32 dissect_netb_no_receive ( tvbuff_t * tvb , packet_info * pinfo _U_ , int offset , proto_tree * tree ) {
 netbios_no_receive_flags ( tvb , tree , offset + NB_FLAGS ) ;
 nb_data2 ( hf_netb_num_data_bytes_accepted , tvb , offset , tree ) ;
 nb_remote_session ( tvb , offset , tree ) ;
 nb_local_session ( tvb , offset , tree ) ;
 return 0 ;
 }