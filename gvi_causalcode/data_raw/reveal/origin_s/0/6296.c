static int dissect_diameter_subscription_id_type ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree _U_ , void * data _U_ ) {
 subscription_id_type = tvb_get_ntohl ( tvb , 0 ) ;
 return 0 ;
 }