static __inline__ int TLV_GET_LEN ( struct tlv_desc * tlv ) {
 return ntohs ( tlv -> tlv_len ) ;
 }