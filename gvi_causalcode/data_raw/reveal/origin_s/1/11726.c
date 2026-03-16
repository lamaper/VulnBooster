static void _ASCIIGetUnicodeSet ( const UConverter * cnv , const USetAdder * sa , UConverterUnicodeSet which , UErrorCode * pErrorCode ) {
 sa -> addRange ( sa -> set , 0 , 0x7f ) ;
 }