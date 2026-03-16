static uint32_t cirrus_get_bpp16_depth ( CirrusVGAState * s ) {
 uint32_t ret = 16 ;
 switch ( s -> cirrus_hidden_dac_data & 0xf ) {
 case 0 : ret = 15 ;
 break ;
 case 1 : ret = 16 ;
 break ;
 default : # ifdef DEBUG_CIRRUS printf ( "cirrus: invalid DAC value %x in 16bpp\n" , ( s -> cirrus_hidden_dac_data & 0xf ) ) ;

 break ;
 }
 return ret ;
 }