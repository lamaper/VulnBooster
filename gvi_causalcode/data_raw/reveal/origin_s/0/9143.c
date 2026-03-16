static guint get_diameter_pdu_len ( packet_info * pinfo _U_ , tvbuff_t * tvb , int offset , void * data _U_ ) {
 return tvb_get_ntoh24 ( tvb , offset + 1 ) ;
 }