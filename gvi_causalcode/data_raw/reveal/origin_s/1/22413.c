static int32_t compareMappingsUnicodeFirst ( const void * context , const void * left , const void * right ) {
 return compareMappings ( ( UCMTable * ) context , ( const UCMapping * ) left , ( UCMTable * ) context , ( const UCMapping * ) right , TRUE ) ;
 }