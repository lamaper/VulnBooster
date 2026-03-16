static const char * _ISCIIgetName ( const UConverter * cnv ) {
 if ( cnv -> extraInfo ) {
 UConverterDataISCII * myData = ( UConverterDataISCII * ) cnv -> extraInfo ;
 return myData -> name ;
 }
 return NULL ;
 }