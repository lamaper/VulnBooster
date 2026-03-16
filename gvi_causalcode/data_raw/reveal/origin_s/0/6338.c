static const char * rsvp_host_get_filter_type ( hostlist_talker_t * host _U_ , conv_filter_type_e filter ) {
 if ( ( filter == CONV_FT_ANY_ADDRESS ) && ( host -> myaddress . type == AT_IPv4 ) ) return "ip.addr" ;
 return CONV_FILTER_INVALID ;
 }