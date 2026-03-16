static UBool U_CALLCONV _enumTypeRange ( const void * context , UChar32 start , UChar32 end , uint32_t value ) {
 return ( ( struct _EnumTypeCallback * ) context ) -> enumRange ( ( ( struct _EnumTypeCallback * ) context ) -> context , start , end + 1 , ( UCharCategory ) value ) ;
 }