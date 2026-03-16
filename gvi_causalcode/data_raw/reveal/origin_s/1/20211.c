static void _UTF16BEReset ( UConverter * cnv , UConverterResetChoice choice ) {
 if ( choice <= UCNV_RESET_TO_UNICODE ) {
 if ( UCNV_GET_VERSION ( cnv ) == 0 ) {
 cnv -> mode = 8 ;
 }
 else {
 cnv -> mode = 0 ;
 }
 }
 if ( choice != UCNV_RESET_TO_UNICODE && UCNV_GET_VERSION ( cnv ) == 1 ) {
 cnv -> fromUnicodeStatus = UCNV_NEED_TO_WRITE_BOM ;
 }
 }