static guint get_opcua_message_len ( packet_info * pinfo _U_ , tvbuff_t * tvb , int offset , void * data _U_ ) {
 gint32 plen ;
 plen = tvb_get_letohl ( tvb , offset + 4 ) ;
 return plen ;
 }