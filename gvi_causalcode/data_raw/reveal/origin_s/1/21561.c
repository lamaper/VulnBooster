static void _ISCIIGetUnicodeSet ( const UConverter * cnv , const USetAdder * sa , UConverterUnicodeSet which , UErrorCode * pErrorCode ) {
 int32_t idx , script ;
 uint8_t mask ;
 sa -> addRange ( sa -> set , 0 , ASCII_END ) ;
 for ( script = DEVANAGARI ;
 script <= MALAYALAM ;
 script ++ ) {
 mask = ( uint8_t ) ( lookupInitialData [ script ] . maskEnum ) ;
 for ( idx = 0 ;
 idx < DELTA ;
 idx ++ ) {
 if ( ( validityTable [ idx ] & mask ) || ( script == TELUGU && idx == 0x31 ) ) {
 sa -> add ( sa -> set , idx + ( script * DELTA ) + INDIC_BLOCK_BEGIN ) ;
 }
 }
 }
 sa -> add ( sa -> set , DANDA ) ;
 sa -> add ( sa -> set , DOUBLE_DANDA ) ;
 sa -> add ( sa -> set , ZWNJ ) ;
 sa -> add ( sa -> set , ZWJ ) ;
 }