static int dissect_nlm4_freeall ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data _U_ ) {
 return dissect_nlm_freeall ( tvb , 0 , pinfo , tree , 4 ) ;
 }