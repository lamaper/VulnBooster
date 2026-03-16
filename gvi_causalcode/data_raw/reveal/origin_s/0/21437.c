static __inline__ int ethtool_validate_duplex ( __u8 duplex ) {
 switch ( duplex ) {
 case DUPLEX_HALF : case DUPLEX_FULL : case DUPLEX_UNKNOWN : return 1 ;
 }
 return 0 ;
 }