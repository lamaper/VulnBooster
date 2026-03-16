static __inline__ void TLV_LIST_STEP ( struct tlv_list_desc * list ) {
 __u16 tlv_space = TLV_ALIGN ( ntohs ( list -> tlv_ptr -> tlv_len ) ) ;
 list -> tlv_ptr = ( struct tlv_desc * ) ( ( char * ) list -> tlv_ptr + tlv_space ) ;
 list -> tlv_space -= tlv_space ;
 }