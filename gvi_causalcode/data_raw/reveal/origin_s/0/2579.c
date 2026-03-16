static uint32_t e1000e_mac_low ## num ## _read ( E1000ECore * core , int index ) {
 return core -> mac [ index ] & ( BIT ( num ) - 1 ) ;
 }

 E1000E_LOW_BITS_READ_FUNC ( 6 ) ;
 E1000E_LOW_BITS_READ_FUNC ( 11 ) ;
 E1000E_LOW_BITS_READ_FUNC ( 13 )