static __inline__ int TLV_LIST_CHECK ( struct tlv_list_desc * list , __u16 exp_type ) {
 return TLV_CHECK ( list -> tlv_ptr , list -> tlv_space , exp_type ) ;
 }