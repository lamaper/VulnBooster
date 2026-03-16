static void U_CALLCONV _UTF32ToUnicodeWithOffsets ( UConverterToUnicodeArgs * pArgs , UErrorCode * pErrorCode ) {
 UConverter * cnv = pArgs -> converter ;
 const char * source = pArgs -> source ;
 const char * sourceLimit = pArgs -> sourceLimit ;
 int32_t * offsets = pArgs -> offsets ;
 int32_t state , offsetDelta ;
 char b ;
 state = cnv -> mode ;
 offsetDelta = 0 ;
 while ( source < sourceLimit && U_SUCCESS ( * pErrorCode ) ) {
 switch ( state ) {
 case 0 : b = * source ;
 if ( b == 0 ) {
 state = 1 ;
 }
 else if ( b == ( char ) 0xff ) {
 state = 5 ;
 }
 else {
 state = 8 ;
 continue ;
 }
 ++ source ;
 break ;
 case 1 : case 2 : case 3 : case 5 : case 6 : case 7 : if ( * source == utf32BOM [ state ] ) {
 ++ state ;
 ++ source ;
 if ( state == 4 ) {
 state = 8 ;
 offsetDelta = ( int32_t ) ( source - pArgs -> source ) ;
 }
 else if ( state == 8 ) {
 state = 9 ;
 offsetDelta = ( int32_t ) ( source - pArgs -> source ) ;
 }
 }
 else {
 int32_t count = ( int32_t ) ( source - pArgs -> source ) ;
 source = pArgs -> source ;
 if ( count == ( state & 3 ) ) {
 }
 else {
 UBool oldFlush = pArgs -> flush ;
 pArgs -> source = utf32BOM + ( state & 4 ) ;
 pArgs -> sourceLimit = pArgs -> source + ( ( state & 3 ) - count ) ;
 pArgs -> flush = FALSE ;
 T_UConverter_toUnicode_UTF32_BE ( pArgs , pErrorCode ) ;
 pArgs -> sourceLimit = sourceLimit ;
 pArgs -> flush = oldFlush ;
 }
 state = 8 ;
 continue ;
 }
 break ;
 case 8 : pArgs -> source = source ;
 if ( offsets == NULL ) {
 T_UConverter_toUnicode_UTF32_BE ( pArgs , pErrorCode ) ;
 }
 else {
 T_UConverter_toUnicode_UTF32_BE_OFFSET_LOGIC ( pArgs , pErrorCode ) ;
 }
 source = pArgs -> source ;
 break ;
 case 9 : pArgs -> source = source ;
 if ( offsets == NULL ) {
 T_UConverter_toUnicode_UTF32_LE ( pArgs , pErrorCode ) ;
 }
 else {
 T_UConverter_toUnicode_UTF32_LE_OFFSET_LOGIC ( pArgs , pErrorCode ) ;
 }
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
 case 8 : T_UConverter_toUnicode_UTF32_BE ( pArgs , pErrorCode ) ;
 break ;
 case 9 : T_UConverter_toUnicode_UTF32_LE ( pArgs , pErrorCode ) ;
 break ;
 default : pArgs -> source = utf32BOM + ( state & 4 ) ;
 pArgs -> sourceLimit = pArgs -> source + ( state & 3 ) ;
 T_UConverter_toUnicode_UTF32_BE ( pArgs , pErrorCode ) ;
 pArgs -> source = source ;
 pArgs -> sourceLimit = sourceLimit ;
 state = 8 ;
 break ;
 }
 }
 cnv -> mode = state ;
 }