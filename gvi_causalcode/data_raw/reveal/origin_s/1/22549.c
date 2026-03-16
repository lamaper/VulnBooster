static void _Latin1GetUnicodeSet ( const UConverter * cnv , const USetAdder * sa , UConverterUnicodeSet which , UErrorCode * pErrorCode ) {
 sa -> addRange ( sa -> set , 0 , 0xff ) ;
 }