static void U_CALLCONV _UTF16ToUnicodeWithOffsets ( UConverterToUnicodeArgs * pArgs , UErrorCode * pErrorCode ) {
 UConverter * cnv = pArgs -> converter ;
 const char * source = pArgs -> source ;
 const char * sourceLimit = pArgs -> sourceLimit ;
 int32_t * offsets = pArgs -> offsets ;
 int32_t state , offsetDelta ;
 uint8_t b ;
 state = cnv -> mode ;
 offsetDelta = 0 ;
 while ( source < sourceLimit && U_SUCCESS ( * pErrorCode ) ) {
 switch ( state ) {
 case 0 : cnv -> toUBytes [ 0 ] = ( uint8_t ) * source ++ ;
 cnv -> toULength = 1 ;
 state = 1 ;
 break ;
 case 1 : b = * source ;
 if ( cnv -> toUBytes [ 0 ] == 0xfe && b == 0xff ) {
 if ( IS_UTF16LE ( cnv ) ) {
 state = 7 ;
 }
 else {
 state = 8 ;
 }
 }
 else if ( cnv -> toUBytes [ 0 ] == 0xff && b == 0xfe ) {
 if ( IS_UTF16BE ( cnv ) ) {
 state = 6 ;
 }
 else {
 state = 9 ;
 }
 }
 else if ( ( IS_UTF16 ( cnv ) && UCNV_GET_VERSION ( cnv ) == 1 ) ) {
 state = 6 ;
 }
 if ( state >= 8 ) {
 ++ source ;
 cnv -> toULength = 0 ;
 offsetDelta = ( int32_t ) ( source - pArgs -> source ) ;
 }
 else if ( state < 6 ) {
 if ( source != pArgs -> source ) {
 source = pArgs -> source ;
 cnv -> toULength = 0 ;
 }
 if ( IS_UTF16LE ( cnv ) ) {
 state = 9 ;
 }
 else {
 state = 8 ;
 }
 }
 else {
 cnv -> toUBytes [ 1 ] = b ;
 cnv -> toULength = 2 ;
 pArgs -> source = source + 1 ;
 cnv -> mode = state + 2 ;
 * pErrorCode = U_ILLEGAL_ESCAPE_SEQUENCE ;
 return ;
 }
 cnv -> mode = state ;
 continue ;
 case 8 : pArgs -> source = source ;
 _UTF16BEToUnicodeWithOffsets ( pArgs , pErrorCode ) ;
 source = pArgs -> source ;
 break ;
 case 9 : pArgs -> source = source ;
 _UTF16LEToUnicodeWithOffsets ( pArgs , pErrorCode ) ;
 source = pArgs -> source ;
 break ;
 default : break ;
 }
 }
 if ( offsets != NULL && offsetDelta != 0 ) {
 int32_t * offsetsLimit = pArgs -> offsets ;
 while ( offsets < offsetsLimit ) {
 * offsets ++ += offsetDelta ;
 }
 }
 pArgs -> source = source ;
 if ( source == sourceLimit && pArgs -> flush ) {
 switch ( state ) {
 case 0 : break ;
 case 8 : _UTF16BEToUnicodeWithOffsets ( pArgs , pErrorCode ) ;
 break ;
 case 9 : _UTF16LEToUnicodeWithOffsets ( pArgs , pErrorCode ) ;
 break ;
 default : break ;
 }
 }
 cnv -> mode = state ;
 }