static guint get_dns_pdu_len ( packet_info * pinfo _U_ , tvbuff_t * tvb , int offset , void * data _U_ ) {
 guint16 plen ;
 plen = tvb_get_ntohs ( tvb , offset ) ;
 return plen + 2 ;
 }