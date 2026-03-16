static int32_t U_CALLCONV compareMappingsUnicodeFirst ( const void * context , const void * left , const void * right ) {
 return compareMappings ( ( UCMTable * ) context , ( const UCMapping * ) left , ( UCMTable * ) context , ( const UCMapping * ) right , TRUE ) ;
 }