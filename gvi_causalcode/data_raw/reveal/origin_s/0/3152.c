static __inline__ void TLV_SET_LEN ( struct tlv_desc * tlv , __u16 len ) {
 tlv -> tlv_len = htons ( len ) ;
 }