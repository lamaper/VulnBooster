static void dissect_OpenLogicalChannel_PDU ( tvbuff_t * tvb _U_ , packet_info * pinfo _U_ , proto_tree * tree _U_ ) {
 asn1_ctx_t asn1_ctx ;
 asn1_ctx_init ( & asn1_ctx , ASN1_ENC_PER , TRUE , pinfo ) ;
 dissect_h245_OpenLogicalChannel ( tvb , 0 , & asn1_ctx , tree , hf_h245_OpenLogicalChannel_PDU ) ;
 }