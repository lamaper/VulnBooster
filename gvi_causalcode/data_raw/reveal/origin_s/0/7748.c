static int32_t u_sprintf_pad_and_justify ( void * context , const u_printf_spec_info * info , const UChar * result , int32_t resultLen ) {
 u_localized_print_string * output = ( u_localized_print_string * ) context ;
 int32_t written = 0 ;
 int32_t lengthOfResult = resultLen ;
 resultLen = ufmt_min ( resultLen , output -> available ) ;
 if ( info -> fWidth != - 1 && resultLen < info -> fWidth ) {
 int32_t paddingLeft = info -> fWidth - resultLen ;
 int32_t outputPos = output -> len - output -> available ;
 if ( paddingLeft + resultLen > output -> available ) {
 paddingLeft = output -> available - resultLen ;
 if ( paddingLeft < 0 ) {
 paddingLeft = 0 ;
 }
 }
 written += paddingLeft ;
 if ( info -> fLeft ) {
 written += u_sprintf_write ( output , result , resultLen ) ;
 u_memset ( & output -> str [ outputPos + resultLen ] , info -> fPadChar , paddingLeft ) ;
 output -> available -= paddingLeft ;
 }
 else {
 u_memset ( & output -> str [ outputPos ] , info -> fPadChar , paddingLeft ) ;
 output -> available -= paddingLeft ;
 written += u_sprintf_write ( output , result , resultLen ) ;
 }
 }
 else {
 written = u_sprintf_write ( output , result , resultLen ) ;
 }
 if ( written >= 0 && lengthOfResult > written ) {
 return lengthOfResult ;
 }
 return written ;
 }