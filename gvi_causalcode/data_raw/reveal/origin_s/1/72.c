static void _UTF16Reset ( UConverter * cnv , UConverterResetChoice choice ) {
 if ( choice <= UCNV_RESET_TO_UNICODE ) {
 cnv -> mode = 0 ;
 }
 if ( choice != UCNV_RESET_TO_UNICODE ) {
 cnv -> fromUnicodeStatus = UCNV_NEED_TO_WRITE_BOM ;
 }
 }