static uint32_t e1000e_mac_low ## num ## _read ( E1000ECore * core , int index ) {
 return core -> mac [ index ] & ( BIT ( num ) - 1 ) ;
 }
