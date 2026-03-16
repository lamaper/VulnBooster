static uint32_t getHostID ( const ILcidPosixMap * this_0 , const char * posixID , UErrorCode * status ) {
 int32_t bestIdx = 0 ;
 int32_t bestIdxDiff = 0 ;
 int32_t posixIDlen = ( int32_t ) uprv_strlen ( posixID ) ;
 uint32_t idx ;
 for ( idx = 0 ;
 idx < this_0 -> numRegions ;
 idx ++ ) {
 int32_t sameChars = idCmp ( posixID , this_0 -> regionMaps [ idx ] . posixID ) ;
 if ( sameChars > bestIdxDiff && this_0 -> regionMaps [ idx ] . posixID [ sameChars ] == 0 ) {
 if ( posixIDlen == sameChars ) {
 return this_0 -> regionMaps [ idx ] . hostID ;
 }
 bestIdxDiff = sameChars ;
 bestIdx = idx ;
 }
 }
 if ( ( posixID [ bestIdxDiff ] == '_' || posixID [ bestIdxDiff ] == '@' ) && this_0 -> regionMaps [ bestIdx ] . posixID [ bestIdxDiff ] == 0 ) {
 * status = U_USING_FALLBACK_WARNING ;
 return this_0 -> regionMaps [ bestIdx ] . hostID ;
 }
 * status = U_ILLEGAL_ARGUMENT_ERROR ;
 return this_0 -> regionMaps -> hostID ;
 }