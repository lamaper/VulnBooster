static const char * rsvp_conv_get_filter_type ( conv_item_t * conv , conv_filter_type_e filter _U_ ) {
 if ( ( filter == CONV_FT_SRC_ADDRESS ) && ( conv -> src_address . type == AT_IPv4 ) ) return "ip.src" ;
 if ( ( filter == CONV_FT_DST_ADDRESS ) && ( conv -> dst_address . type == AT_IPv4 ) ) return "ip.dst" ;
 if ( ( filter == CONV_FT_ANY_ADDRESS ) && ( conv -> src_address . type == AT_IPv4 ) ) return "ip.addr" ;
 return CONV_FILTER_INVALID ;
 }