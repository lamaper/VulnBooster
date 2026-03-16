static __inline__ int TLV_SET ( void * tlv , __u16 type , void * data , __u16 len ) {
 struct tlv_desc * tlv_ptr ;
 int tlv_len ;
 tlv_len = TLV_LENGTH ( len ) ;
 tlv_ptr = ( struct tlv_desc * ) tlv ;
 tlv_ptr -> tlv_type = htons ( type ) ;
 tlv_ptr -> tlv_len = htons ( tlv_len ) ;
 if ( len && data ) {
 memcpy ( TLV_DATA ( tlv_ptr ) , data , len ) ;
 memset ( TLV_DATA ( tlv_ptr ) + len , 0 , TLV_SPACE ( len ) - tlv_len ) ;
 }
 return TLV_SPACE ( len ) ;
 }