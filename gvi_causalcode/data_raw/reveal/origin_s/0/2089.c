static UBool U_CALLCONV _enumPropertyStartsRange ( const void * context , UChar32 start , UChar32 end , uint32_t value ) {
 ( void ) end ;
 ( void ) value ;
 const USetAdder * sa = ( const USetAdder * ) context ;
 sa -> add ( sa -> set , start ) ;
 return TRUE ;
 }