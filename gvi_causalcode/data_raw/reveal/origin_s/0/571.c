static __inline__ __u32 ethtool_cmd_speed ( const struct ethtool_cmd * ep ) {
 return ( ep -> speed_hi << 16 ) | ep -> speed ;
 }