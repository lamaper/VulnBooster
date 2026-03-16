static void U_CALLCONV _ASCIIGetUnicodeSet ( const UConverter * cnv , const USetAdder * sa , UConverterUnicodeSet which , UErrorCode * pErrorCode ) {
 ( void ) cnv ;
 ( void ) which ;
 ( void ) pErrorCode ;
 sa -> addRange ( sa -> set , 0 , 0x7f ) ;
 }