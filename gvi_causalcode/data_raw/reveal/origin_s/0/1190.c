static conversation_t * find_or_create_conversation_noaddrb ( packet_info * pinfo , gboolean request ) {
 conversation_t * conv = NULL ;
 address * addr_a ;
 address * addr_b ;
 guint32 port_a ;
 guint32 port_b ;
 if ( request ) {
 addr_a = & pinfo -> src ;
 addr_b = & pinfo -> dst ;
 port_a = pinfo -> srcport ;
 port_b = pinfo -> destport ;
 }
 else {
 addr_a = & pinfo -> dst ;
 addr_b = & pinfo -> src ;
 port_a = pinfo -> destport ;
 port_b = pinfo -> srcport ;
 }
 if ( ( conv = find_conversation ( pinfo -> num , addr_a , addr_b , conversation_pt_to_endpoint_type ( pinfo -> ptype ) , port_a , port_b , NO_ADDR_B | NO_PORT_B ) ) != NULL ) {
 if ( pinfo -> num > conv -> last_frame ) {
 conv -> last_frame = pinfo -> num ;
 }
 }
 else {
 conv = conversation_new ( pinfo -> num , & pinfo -> src , & pinfo -> dst , conversation_pt_to_endpoint_type ( pinfo -> ptype ) , pinfo -> srcport , pinfo -> destport , NO_ADDR_B | NO_PORT_B ) ;
 }
 return conv ;
 }