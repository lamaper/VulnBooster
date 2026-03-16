static guint32 dissect_netb_data_only_last ( tvbuff_t * tvb , packet_info * pinfo _U_ , int offset , proto_tree * tree ) {
 guint8 remote_session , local_session ;
 netbios_data_only_flags ( tvb , tree , offset + NB_FLAGS ) ;
 nb_resync_indicator ( tvb , offset , tree , "DATA ONLY LAST" ) ;
 nb_xmit_corrl ( tvb , offset , tree ) ;
 nb_resp_corrl ( tvb , offset , tree ) ;
 remote_session = nb_remote_session ( tvb , offset , tree ) ;
 local_session = nb_local_session ( tvb , offset , tree ) ;
 return ( remote_session << 8 ) + local_session ;
 }