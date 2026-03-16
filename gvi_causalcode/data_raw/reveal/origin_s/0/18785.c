static __inline__ void TLV_SET_TYPE ( struct tlv_desc * tlv , __u16 type ) {
 tlv -> tlv_type = htons ( type ) ;
 }