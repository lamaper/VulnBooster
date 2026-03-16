static __inline__ unsigned int dccp_packet_hdr_len ( const __u8 type ) {
 if ( type == DCCP_PKT_DATA ) return 0 ;
 if ( type == DCCP_PKT_DATAACK || type == DCCP_PKT_ACK || type == DCCP_PKT_SYNC || type == DCCP_PKT_SYNCACK || type == DCCP_PKT_CLOSE || type == DCCP_PKT_CLOSEREQ ) return sizeof ( struct dccp_hdr_ack_bits ) ;
 if ( type == DCCP_PKT_REQUEST ) return sizeof ( struct dccp_hdr_request ) ;
 if ( type == DCCP_PKT_RESPONSE ) return sizeof ( struct dccp_hdr_response ) ;
 return sizeof ( struct dccp_hdr_reset ) ;
 }