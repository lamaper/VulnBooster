static void _UTF7Reset ( UConverter * cnv , UConverterResetChoice choice ) {
 if ( choice <= UCNV_RESET_TO_UNICODE ) {
 cnv -> toUnicodeStatus = 0x1000000 ;
 cnv -> toULength = 0 ;
 }
 if ( choice != UCNV_RESET_TO_UNICODE ) {
 cnv -> fromUnicodeStatus = ( cnv -> fromUnicodeStatus & 0xf0000000 ) | 0x1000000 ;
 }
 }