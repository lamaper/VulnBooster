static void _CompoundText_GetUnicodeSet ( const UConverter * cnv , const USetAdder * sa , UConverterUnicodeSet which , UErrorCode * pErrorCode ) {
 UConverterDataCompoundText * myConverterData = ( UConverterDataCompoundText * ) cnv -> extraInfo ;
 int32_t i ;
 for ( i = 1 ;
 i < NUM_OF_CONVERTERS ;
 i ++ ) {
 ucnv_MBCSGetUnicodeSetForUnicode ( myConverterData -> myConverterArray [ i ] , sa , which , pErrorCode ) ;
 }
 sa -> add ( sa -> set , 0x0000 ) ;
 sa -> add ( sa -> set , 0x0009 ) ;
 sa -> add ( sa -> set , 0x000A ) ;
 sa -> addRange ( sa -> set , 0x0020 , 0x007F ) ;
 sa -> addRange ( sa -> set , 0x00A0 , 0x00FF ) ;
 }