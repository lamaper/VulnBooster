static void U_CALLCONV _Latin1GetUnicodeSet ( const UConverter * cnv , const USetAdder * sa , UConverterUnicodeSet which , UErrorCode * pErrorCode ) {
 ( void ) cnv ;
 ( void ) which ;
 ( void ) pErrorCode ;
 sa -> addRange ( sa -> set , 0 , 0xff ) ;
 }