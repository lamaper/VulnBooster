static guint32 dissect_netb_name_in_conflict ( tvbuff_t * tvb , packet_info * pinfo _U_ , int offset , proto_tree * tree ) {
 netbios_add_name ( "Name In Conflict" , tvb , offset + NB_RECVER_NAME , tree ) ;
 netbios_add_name ( "Sender's Name" , tvb , offset + NB_SENDER_NAME , tree ) ;
 return 0 ;
 }