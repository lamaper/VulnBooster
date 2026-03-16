static Datum string_to_datum ( const char * str , Oid datatype ) {
 Assert ( str != NULL ) ;
 if ( datatype == NAMEOID ) return DirectFunctionCall1 ( namein , CStringGetDatum ( str ) ) ;
 else if ( datatype == BYTEAOID ) return DirectFunctionCall1 ( byteain , CStringGetDatum ( str ) ) ;
 else return CStringGetTextDatum ( str ) ;
 }