static guint get_pcp_message_len ( packet_info * pinfo _U_ , tvbuff_t * tvb , int offset , void * data _U_ ) {
 return ( guint ) tvb_get_ntohl ( tvb , offset ) ;
 }