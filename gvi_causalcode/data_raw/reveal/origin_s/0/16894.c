static __inline__ int TLV_CHECK ( const void * tlv , __u16 space , __u16 exp_type ) {
 return TLV_OK ( tlv , space ) && ( ntohs ( ( ( struct tlv_desc * ) tlv ) -> tlv_type ) == exp_type ) ;
 }