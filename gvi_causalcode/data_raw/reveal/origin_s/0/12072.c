static guint32 dissect_netb_add_group_name ( tvbuff_t * tvb , packet_info * pinfo _U_ , int offset , proto_tree * tree ) {
 nb_resp_corrl ( tvb , offset , tree ) ;
 netbios_add_name ( "Group name to add" , tvb , offset + NB_SENDER_NAME , tree ) ;
 return 0 ;
 }