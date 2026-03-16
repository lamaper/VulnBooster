static __inline__ void TLV_LIST_INIT ( struct tlv_list_desc * list , void * data , __u32 space ) {
 list -> tlv_ptr = ( struct tlv_desc * ) data ;
 list -> tlv_space = space ;
 }