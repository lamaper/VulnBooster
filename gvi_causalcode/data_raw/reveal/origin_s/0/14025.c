static guint32 dissect_netb_session_alive ( tvbuff_t * tvb , packet_info * pinfo _U_ , int offset , proto_tree * tree ) {
 nb_remote_session ( tvb , offset , tree ) ;
 nb_local_session ( tvb , offset , tree ) ;
 return 0 ;
 }