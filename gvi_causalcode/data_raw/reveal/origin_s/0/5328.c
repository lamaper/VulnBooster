static inline int client_to_server ( packet_info * pinfo ) {
 return pinfo -> destport == PCP_PORT || pinfo -> destport == PMPROXY_PORT ;
 }