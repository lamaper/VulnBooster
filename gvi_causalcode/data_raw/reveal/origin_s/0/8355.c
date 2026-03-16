static __inline__ int ethtool_validate_speed ( __u32 speed ) {
 return speed <= INT_MAX || speed == SPEED_UNKNOWN ;
 }