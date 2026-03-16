static inline bool e1000e_rx_csum_enabled ( E1000ECore * core ) {
 return ( core -> mac [ RXCSUM ] & E1000_RXCSUM_PCSD ) ? false : true ;
 }