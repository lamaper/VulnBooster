static void _LMBCSClose ( UConverter * _this ) {
 if ( _this -> extraInfo != NULL ) {
 ulmbcs_byte_t Ix ;
 UConverterDataLMBCS * extraInfo = ( UConverterDataLMBCS * ) _this -> extraInfo ;
 for ( Ix = 0 ;
 Ix <= ULMBCS_GRP_LAST ;
 Ix ++ ) {
 if ( extraInfo -> OptGrpConverter [ Ix ] != NULL ) ucnv_unloadSharedDataIfReady ( extraInfo -> OptGrpConverter [ Ix ] ) ;
 }
 if ( ! _this -> isExtraLocal ) {
 uprv_free ( _this -> extraInfo ) ;
 _this -> extraInfo = NULL ;
 }
 }
 }