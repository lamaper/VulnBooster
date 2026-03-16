static const char * getPosixID ( const ILcidPosixMap * this_0 , uint32_t hostID ) {
 uint32_t i ;
 for ( i = 0 ;
 i <= this_0 -> numRegions ;
 i ++ ) {
 if ( this_0 -> regionMaps [ i ] . hostID == hostID ) {
 return this_0 -> regionMaps [ i ] . posixID ;
 }
 }
 return this_0 -> regionMaps [ 0 ] . posixID ;
 }