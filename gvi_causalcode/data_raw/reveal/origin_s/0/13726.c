static __inline__ int TLV_CHECK_TYPE ( struct tlv_desc * tlv , __u16 type ) {
 return ( ntohs ( tlv -> tlv_type ) == type ) ;
 }