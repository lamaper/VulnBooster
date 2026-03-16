static void _CompoundTextClose ( UConverter * converter ) {
 UConverterDataCompoundText * myConverterData = ( UConverterDataCompoundText * ) ( converter -> extraInfo ) ;
 int32_t i ;
 if ( converter -> extraInfo != NULL ) {
 for ( i = 0 ;
 i < NUM_OF_CONVERTERS ;
 i ++ ) {
 if ( myConverterData -> myConverterArray [ i ] != NULL ) {
 ucnv_unloadSharedDataIfReady ( myConverterData -> myConverterArray [ i ] ) ;
 }
 }
 uprv_free ( converter -> extraInfo ) ;
 }
 }