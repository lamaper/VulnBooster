static __inline__ void ethtool_cmd_speed_set ( struct ethtool_cmd * ep , __u32 speed ) {
 ep -> speed = ( __u16 ) ( speed & 0xFFFF ) ;
 ep -> speed_hi = ( __u16 ) ( speed >> 16 ) ;
 }