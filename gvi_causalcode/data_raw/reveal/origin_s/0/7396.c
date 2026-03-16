static const char * U_CALLCONV _ISCIIgetName ( const UConverter * cnv ) {
 if ( cnv -> extraInfo ) {
 UConverterDataISCII * myData = ( UConverterDataISCII * ) cnv -> extraInfo ;
 return myData -> name ;
 }
 return NULL ;
 }