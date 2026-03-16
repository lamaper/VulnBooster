static inline __u8 ip_reply_arg_flowi_flags ( const struct ip_reply_arg * arg ) {
 return ( arg -> flags & IP_REPLY_ARG_NOSRCCHECK ) ? FLOWI_FLAG_ANYSRC : 0 ;
 }