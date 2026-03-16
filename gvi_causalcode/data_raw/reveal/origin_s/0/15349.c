static guint32 dissect_netb_datagram_bcast ( tvbuff_t * tvb , packet_info * pinfo _U_ , int offset , proto_tree * tree ) {
 if ( tvb_memeql ( tvb , offset + NB_SENDER_NAME , zeroes , 10 ) == 0 ) {
 proto_tree_add_item ( tree , hf_netb_datagram_bcast_mac , tvb , offset + NB_SENDER_NAME + 10 , 6 , ENC_NA ) ;
 }
 else {
 netbios_add_name ( "Sender's Name" , tvb , offset + NB_SENDER_NAME , tree ) ;
 }
 return 0 ;
 }