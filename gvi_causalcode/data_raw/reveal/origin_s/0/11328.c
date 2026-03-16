static void CnvExtClose ( NewConverter * cnvData ) {
 CnvExtData * extData = ( CnvExtData * ) cnvData ;
 if ( extData != NULL ) {
 utm_close ( extData -> toUTable ) ;
 utm_close ( extData -> toUUChars ) ;
 utm_close ( extData -> fromUTableUChars ) ;
 utm_close ( extData -> fromUTableValues ) ;
 utm_close ( extData -> fromUBytes ) ;
 uprv_free ( extData ) ;
 }
 }