static void _LMBCSFromUnicode ( UConverterFromUnicodeArgs * args , UErrorCode * err ) {
 ulmbcs_byte_t lastConverterIndex = 0 ;
 UChar uniChar ;
 ulmbcs_byte_t LMBCS [ ULMBCS_CHARSIZE_MAX ] ;
 ulmbcs_byte_t * pLMBCS ;
 int32_t bytes_written ;
 UBool groups_tried [ ULMBCS_GRP_LAST + 1 ] ;
 UConverterDataLMBCS * extraInfo = ( UConverterDataLMBCS * ) args -> converter -> extraInfo ;
 int sourceIndex = 0 ;
 ulmbcs_byte_t OldConverterIndex = 0 ;
 while ( args -> source < args -> sourceLimit && ! U_FAILURE ( * err ) ) {
 OldConverterIndex = extraInfo -> localeConverterIndex ;
 if ( args -> target >= args -> targetLimit ) {
 * err = U_BUFFER_OVERFLOW_ERROR ;
 break ;
 }
 uniChar = * ( args -> source ) ;
 bytes_written = 0 ;
 pLMBCS = LMBCS ;
 if ( ( uniChar >= 0x80 ) && ( uniChar <= 0xff ) && ( uniChar != 0xB1 ) && ( uniChar != 0xD7 ) && ( uniChar != 0xF7 ) && ( uniChar != 0xB0 ) && ( uniChar != 0xB4 ) && ( uniChar != 0xB6 ) && ( uniChar != 0xA7 ) && ( uniChar != 0xA8 ) ) {
 extraInfo -> localeConverterIndex = ULMBCS_GRP_L1 ;
 }
 if ( ( ( uniChar > ULMBCS_C0END ) && ( uniChar < ULMBCS_C1START ) ) || uniChar == 0 || uniChar == ULMBCS_HT || uniChar == ULMBCS_CR || uniChar == ULMBCS_LF || uniChar == ULMBCS_123SYSTEMRANGE ) {
 * pLMBCS ++ = ( ulmbcs_byte_t ) uniChar ;
 bytes_written = 1 ;
 }
 if ( ! bytes_written ) {
 ulmbcs_byte_t group = FindLMBCSUniRange ( uniChar ) ;
 if ( group == ULMBCS_GRP_UNICODE ) {
 pLMBCS += LMBCSConvertUni ( pLMBCS , uniChar ) ;
 bytes_written = ( int32_t ) ( pLMBCS - LMBCS ) ;
 }
 else if ( group == ULMBCS_GRP_CTRL ) {
 if ( uniChar <= ULMBCS_C0END ) {
 * pLMBCS ++ = ULMBCS_GRP_CTRL ;
 * pLMBCS ++ = ( ulmbcs_byte_t ) ( ULMBCS_CTRLOFFSET + uniChar ) ;
 }
 else if ( uniChar >= ULMBCS_C1START && uniChar <= ULMBCS_C1START + ULMBCS_CTRLOFFSET ) {
 * pLMBCS ++ = ULMBCS_GRP_CTRL ;
 * pLMBCS ++ = ( ulmbcs_byte_t ) ( uniChar & 0x00FF ) ;
 }
 bytes_written = ( int32_t ) ( pLMBCS - LMBCS ) ;
 }
 else if ( group < ULMBCS_GRP_UNICODE ) {
 bytes_written = ( int32_t ) LMBCSConversionWorker ( extraInfo , group , pLMBCS , & uniChar , & lastConverterIndex , groups_tried ) ;
 }
 if ( ! bytes_written ) {
 uprv_memset ( groups_tried , 0 , sizeof ( groups_tried ) ) ;
 if ( ( extraInfo -> OptGroup != 1 ) && ( ULMBCS_AMBIGUOUS_MATCH ( group , extraInfo -> OptGroup ) ) ) {
 if ( extraInfo -> localeConverterIndex < ULMBCS_DOUBLEOPTGROUP_START ) {
 bytes_written = LMBCSConversionWorker ( extraInfo , ULMBCS_GRP_L1 , pLMBCS , & uniChar , & lastConverterIndex , groups_tried ) ;
 if ( ! bytes_written ) {
 bytes_written = LMBCSConversionWorker ( extraInfo , ULMBCS_GRP_EXCEPT , pLMBCS , & uniChar , & lastConverterIndex , groups_tried ) ;
 }
 if ( ! bytes_written ) {
 bytes_written = LMBCSConversionWorker ( extraInfo , extraInfo -> localeConverterIndex , pLMBCS , & uniChar , & lastConverterIndex , groups_tried ) ;
 }
 }
 else {
 bytes_written = LMBCSConversionWorker ( extraInfo , extraInfo -> localeConverterIndex , pLMBCS , & uniChar , & lastConverterIndex , groups_tried ) ;
 }
 }
 if ( ! bytes_written && ( extraInfo -> localeConverterIndex ) && ( ULMBCS_AMBIGUOUS_MATCH ( group , extraInfo -> localeConverterIndex ) ) ) {
 bytes_written = ( int32_t ) LMBCSConversionWorker ( extraInfo , extraInfo -> localeConverterIndex , pLMBCS , & uniChar , & lastConverterIndex , groups_tried ) ;
 }
 if ( ! bytes_written && ( lastConverterIndex ) && ( ULMBCS_AMBIGUOUS_MATCH ( group , lastConverterIndex ) ) ) {
 bytes_written = ( int32_t ) LMBCSConversionWorker ( extraInfo , lastConverterIndex , pLMBCS , & uniChar , & lastConverterIndex , groups_tried ) ;
 }
 if ( ! bytes_written ) {
 ulmbcs_byte_t grp_start ;
 ulmbcs_byte_t grp_end ;
 ulmbcs_byte_t grp_ix ;
 grp_start = ( ulmbcs_byte_t ) ( ( group == ULMBCS_AMBIGUOUS_MBCS ) ? ULMBCS_DOUBLEOPTGROUP_START : ULMBCS_GRP_L1 ) ;
 grp_end = ( ulmbcs_byte_t ) ( ( group == ULMBCS_AMBIGUOUS_MBCS ) ? ULMBCS_GRP_LAST : ULMBCS_GRP_TH ) ;
 if ( group == ULMBCS_AMBIGUOUS_ALL ) {
 grp_start = ULMBCS_GRP_L1 ;
 grp_end = ULMBCS_GRP_LAST ;
 }
 for ( grp_ix = grp_start ;
 grp_ix <= grp_end && ! bytes_written ;
 grp_ix ++ ) {
 if ( extraInfo -> OptGrpConverter [ grp_ix ] && ! groups_tried [ grp_ix ] ) {
 bytes_written = ( int32_t ) LMBCSConversionWorker ( extraInfo , grp_ix , pLMBCS , & uniChar , & lastConverterIndex , groups_tried ) ;
 }
 }
 if ( ! bytes_written && grp_start == ULMBCS_GRP_L1 ) {
 bytes_written = ( int32_t ) LMBCSConversionWorker ( extraInfo , ULMBCS_GRP_EXCEPT , pLMBCS , & uniChar , & lastConverterIndex , groups_tried ) ;
 }
 }
 if ( ! bytes_written ) {
 pLMBCS += LMBCSConvertUni ( pLMBCS , uniChar ) ;
 bytes_written = ( int32_t ) ( pLMBCS - LMBCS ) ;
 }
 }
 }
 args -> source ++ ;
 pLMBCS = LMBCS ;
 while ( args -> target < args -> targetLimit && bytes_written -- ) {
 * ( args -> target ) ++ = * pLMBCS ++ ;
 if ( args -> offsets ) {
 * ( args -> offsets ) ++ = sourceIndex ;
 }
 }
 sourceIndex ++ ;
 if ( bytes_written > 0 ) {
 uint8_t * pErrorBuffer = args -> converter -> charErrorBuffer ;
 * err = U_BUFFER_OVERFLOW_ERROR ;
 args -> converter -> charErrorBufferLength = ( int8_t ) bytes_written ;
 while ( bytes_written -- ) {
 * pErrorBuffer ++ = * pLMBCS ++ ;
 }
 }
 extraInfo -> localeConverterIndex = OldConverterIndex ;
 }
 }