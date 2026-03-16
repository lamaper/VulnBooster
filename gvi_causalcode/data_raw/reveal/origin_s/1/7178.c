static int dissect_h225_H245TransportAddress ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 ipv4_address = 0 ;
 ipv6_address = ipv6_address_zeros ;
 ip_port = 0 ;
 offset = dissect_per_choice ( tvb , offset , actx , tree , hf_index , ett_h225_H245TransportAddress , H245TransportAddress_choice , NULL ) ;

 if ( h225_pi ) {
 h225_pi -> is_h245 = TRUE ;
 h225_pi -> h245_address = ipv4_address ;
 h225_pi -> h245_port = ip_port ;
 }
 if ( ! actx -> pinfo -> fd -> flags . visited && h245_handle && ip_port != 0 ) {
 address src_addr ;
 conversation_t * conv = NULL ;
 if ( ipv4_address != 0 ) {
 set_address ( & src_addr , AT_IPv4 , 4 , & ipv4_address ) ;
 }
 else if ( memcmp ( ipv6_address . bytes , ipv6_address_zeros . bytes , sizeof ( ipv6_address . bytes ) ) != 0 ) {
 set_address ( & src_addr , AT_IPv6 , 16 , ipv6_address . bytes ) ;
 }
 else {
 return offset ;
 }
 conv = find_conversation ( actx -> pinfo -> num , & src_addr , & src_addr , PT_TCP , ip_port , ip_port , NO_ADDR_B | NO_PORT_B ) ;
 if ( ! conv ) {
 conv = conversation_new ( actx -> pinfo -> num , & src_addr , & src_addr , PT_TCP , ip_port , ip_port , NO_ADDR2 | NO_PORT2 ) ;
 conversation_set_dissector ( conv , h245_handle ) ;
 }
 }
 return offset ;
 }