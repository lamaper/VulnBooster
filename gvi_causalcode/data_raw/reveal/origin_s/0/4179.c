static void U_CALLCONV _HZ_GetUnicodeSet ( const UConverter * cnv , const USetAdder * sa , UConverterUnicodeSet which , UErrorCode * pErrorCode ) {
 sa -> addRange ( sa -> set , 0 , 0x7f ) ;
 ucnv_MBCSGetFilteredUnicodeSetForUnicode ( ( ( UConverterDataHZ * ) cnv -> extraInfo ) -> gbConverter -> sharedData , sa , which , UCNV_SET_FILTER_HZ , pErrorCode ) ;
 }