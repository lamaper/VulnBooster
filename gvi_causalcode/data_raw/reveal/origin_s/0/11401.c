static int dissect_RasMessage_PDU ( tvbuff_t * tvb _U_ , packet_info * pinfo _U_ , proto_tree * tree _U_ , void * data _U_ ) {
 int offset = 0 ;
 asn1_ctx_t asn1_ctx ;
 asn1_ctx_init ( & asn1_ctx , ASN1_ENC_PER , TRUE , pinfo ) ;
 offset = dissect_h225_RasMessage ( tvb , offset , & asn1_ctx , tree , hf_h225_RasMessage_PDU ) ;
 offset += 7 ;
 offset >>= 3 ;
 return offset ;
 }