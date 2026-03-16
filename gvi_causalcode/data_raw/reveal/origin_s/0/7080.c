static __inline__ int TLV_OK ( const void * tlv , __u16 space ) {
 return ( space >= TLV_SPACE ( 0 ) ) && ( ntohs ( ( ( struct tlv_desc * ) tlv ) -> tlv_len ) <= space ) ;
 }