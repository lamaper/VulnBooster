static void U_CALLCONV _LMBCSOpen ## n ( UConverter * _this , UConverterLoadArgs * pArgs , UErrorCode * err ) \ {
 _LMBCSOpenWorker ( _this , pArgs , err , n ) ;
 }
 static void _LMBCSOpenWorker ( UConverter * _this , UConverterLoadArgs * pArgs , UErrorCode * err , ulmbcs_byte_t OptGroup ) {
 UConverterDataLMBCS * extraInfo = ( UConverterDataLMBCS * ) uprv_malloc ( sizeof ( UConverterDataLMBCS ) ) ;
 _this -> extraInfo = extraInfo ;
 if ( extraInfo != NULL ) {
 UConverterNamePieces stackPieces ;
 UConverterLoadArgs stackArgs = UCNV_LOAD_ARGS_INITIALIZER ;
 ulmbcs_byte_t i ;
 uprv_memset ( extraInfo , 0 , sizeof ( UConverterDataLMBCS ) ) ;
 stackArgs . onlyTestIsLoadable = pArgs -> onlyTestIsLoadable ;
 for ( i = 0 ;
 i <= ULMBCS_GRP_LAST && U_SUCCESS ( * err ) ;
 i ++ ) {
 if ( OptGroupByteToCPName [ i ] != NULL ) {
 extraInfo -> OptGrpConverter [ i ] = ucnv_loadSharedData ( OptGroupByteToCPName [ i ] , & stackPieces , & stackArgs , err ) ;
 }
 }
 if ( U_FAILURE ( * err ) || pArgs -> onlyTestIsLoadable ) {
 _LMBCSClose ( _this ) ;
 return ;
 }
 extraInfo -> OptGroup = OptGroup ;
 extraInfo -> localeConverterIndex = FindLMBCSLocale ( pArgs -> locale ) ;
 }
 else {
 * err = U_MEMORY_ALLOCATION_ERROR ;
 }
 }
 U_CDECL_BEGIN static void U_CALLCONV _LMBCSClose ( UConverter * _this ) {
 if ( _this -> extraInfo != NULL ) {
 ulmbcs_byte_t Ix ;
 UConverterDataLMBCS * extraInfo = ( UConverterDataLMBCS * ) _this -> extraInfo ;
 for ( Ix = 0 ;
 Ix <= ULMBCS_GRP_LAST ;
 Ix ++ ) {
 if ( extraInfo -> OptGrpConverter [ Ix ] != NULL ) ucnv_unloadSharedDataIfReady ( extraInfo -> OptGrpConverter [ Ix ] ) ;
 }
 if ( ! _this -> isExtraLocal ) {
 uprv_free ( _this -> extraInfo ) ;
 _this -> extraInfo = NULL ;
 }
 }
 }
 typedef struct LMBCSClone {
 UConverter cnv ;
 UConverterDataLMBCS lmbcs ;
 }
 LMBCSClone ;
 static UConverter * U_CALLCONV _LMBCSSafeClone ( const UConverter * cnv , void * stackBuffer , int32_t * pBufferSize , UErrorCode * status ) {
 ( void ) status ;
 LMBCSClone * newLMBCS ;
 UConverterDataLMBCS * extraInfo ;
 int32_t i ;
 if ( * pBufferSize <= 0 ) {
 * pBufferSize = ( int32_t ) sizeof ( LMBCSClone ) ;
 return NULL ;
 }
 extraInfo = ( UConverterDataLMBCS * ) cnv -> extraInfo ;
 newLMBCS = ( LMBCSClone * ) stackBuffer ;
 uprv_memcpy ( & newLMBCS -> lmbcs , extraInfo , sizeof ( UConverterDataLMBCS ) ) ;
 for ( i = 0 ;
 i <= ULMBCS_GRP_LAST ;
 ++ i ) {
 if ( extraInfo -> OptGrpConverter [ i ] != NULL ) {
 ucnv_incrementRefCount ( extraInfo -> OptGrpConverter [ i ] ) ;
 }
 }
 newLMBCS -> cnv . extraInfo = & newLMBCS -> lmbcs ;
 newLMBCS -> cnv . isExtraLocal = TRUE ;
 return & newLMBCS -> cnv ;
 }
 static size_t LMBCSConversionWorker ( UConverterDataLMBCS * extraInfo , ulmbcs_byte_t group , ulmbcs_byte_t * pStartLMBCS , UChar * pUniChar , ulmbcs_byte_t * lastConverterIndex , UBool * groups_tried ) {
 ulmbcs_byte_t * pLMBCS = pStartLMBCS ;
 UConverterSharedData * xcnv = extraInfo -> OptGrpConverter [ group ] ;
 int bytesConverted ;
 uint32_t value ;
 ulmbcs_byte_t firstByte ;
 U_ASSERT ( xcnv ) ;
 U_ASSERT ( group < ULMBCS_GRP_UNICODE ) ;
 bytesConverted = ucnv_MBCSFromUChar32 ( xcnv , * pUniChar , & value , FALSE ) ;
 if ( bytesConverted > 0 ) {
 firstByte = ( ulmbcs_byte_t ) ( value >> ( ( bytesConverted - 1 ) * 8 ) ) ;
 }
 else {
 groups_tried [ group ] = TRUE ;
 return 0 ;
 }
 * lastConverterIndex = group ;
 U_ASSERT ( ( firstByte <= ULMBCS_C0END ) || ( firstByte >= ULMBCS_C1START ) || ( group == ULMBCS_GRP_EXCEPT ) ) ;
 if ( group != ULMBCS_GRP_EXCEPT && extraInfo -> OptGroup != group ) {
 * pLMBCS ++ = group ;
 if ( bytesConverted == 1 && group >= ULMBCS_DOUBLEOPTGROUP_START ) {
 * pLMBCS ++ = group ;
 }
 }
 if ( bytesConverted == 1 && firstByte < 0x20 ) return 0 ;
 switch ( bytesConverted ) {
 case 4 : * pLMBCS ++ = ( ulmbcs_byte_t ) ( value >> 24 ) ;
 U_FALLTHROUGH ;
 case 3 : * pLMBCS ++ = ( ulmbcs_byte_t ) ( value >> 16 ) ;
 U_FALLTHROUGH ;
 case 2 : * pLMBCS ++ = ( ulmbcs_byte_t ) ( value >> 8 ) ;
 U_FALLTHROUGH ;
 case 1 : * pLMBCS ++ = ( ulmbcs_byte_t ) value ;
 U_FALLTHROUGH ;
 default : break ;
 }
 return ( pLMBCS - pStartLMBCS ) ;
 }
 static size_t LMBCSConvertUni ( ulmbcs_byte_t * pLMBCS , UChar uniChar ) {
 uint8_t LowCh = ( uint8_t ) ( uniChar & 0x00FF ) ;
 uint8_t HighCh = ( uint8_t ) ( uniChar >> 8 ) ;
 * pLMBCS ++ = ULMBCS_GRP_UNICODE ;
 if ( LowCh == 0 ) {
 * pLMBCS ++ = ULMBCS_UNICOMPATZERO ;
 * pLMBCS ++ = HighCh ;
 }
 else {
 * pLMBCS ++ = HighCh ;
 * pLMBCS ++ = LowCh ;
 }
 return ULMBCS_UNICODE_SIZE ;
 }
 static void U_CALLCONV _LMBCSFromUnicode ( UConverterFromUnicodeArgs * args , UErrorCode * err ) {
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
 static UChar GetUniFromLMBCSUni ( char const * * ppLMBCSin ) {
 uint8_t HighCh = * ( * ppLMBCSin ) ++ ;
 uint8_t LowCh = * ( * ppLMBCSin ) ++ ;
 if ( HighCh == ULMBCS_UNICOMPATZERO ) {
 HighCh = LowCh ;
 LowCh = 0 ;
 }
 return ( UChar ) ( ( HighCh << 8 ) | LowCh ) ;
 }

 * err = U_TRUNCATED_CHAR_FOUND ;
 args -> source = args -> sourceLimit ;
 return 0xffff ;
 }
 static UChar32 U_CALLCONV _LMBCSGetNextUCharWorker ( UConverterToUnicodeArgs * args , UErrorCode * err ) {
 UChar32 uniChar = 0 ;
 ulmbcs_byte_t CurByte ;
 if ( args -> source >= args -> sourceLimit ) {
 * err = U_ILLEGAL_ARGUMENT_ERROR ;
 return 0xffff ;
 }
 CurByte = * ( ( ulmbcs_byte_t * ) ( args -> source ++ ) ) ;
 if ( ( ( CurByte > ULMBCS_C0END ) && ( CurByte < ULMBCS_C1START ) ) || ( CurByte == 0 ) || CurByte == ULMBCS_HT || CurByte == ULMBCS_CR || CurByte == ULMBCS_LF || CurByte == ULMBCS_123SYSTEMRANGE ) {
 uniChar = CurByte ;
 }
 else {
 UConverterDataLMBCS * extraInfo ;
 ulmbcs_byte_t group ;
 UConverterSharedData * cnv ;
 if ( CurByte == ULMBCS_GRP_CTRL ) {
 ulmbcs_byte_t C0C1byte ;
 CHECK_SOURCE_LIMIT ( 1 ) ;
 C0C1byte = * ( args -> source ) ++ ;
 uniChar = ( C0C1byte < ULMBCS_C1START ) ? C0C1byte - ULMBCS_CTRLOFFSET : C0C1byte ;
 }
 else if ( CurByte == ULMBCS_GRP_UNICODE ) {
 CHECK_SOURCE_LIMIT ( 2 ) ;
 return GetUniFromLMBCSUni ( & ( args -> source ) ) ;
 }
 else if ( CurByte <= ULMBCS_CTRLOFFSET ) {
 group = CurByte ;
 extraInfo = ( UConverterDataLMBCS * ) args -> converter -> extraInfo ;
 if ( group > ULMBCS_GRP_LAST || ( cnv = extraInfo -> OptGrpConverter [ group ] ) == NULL ) {
 * err = U_INVALID_CHAR_FOUND ;
 }
 else if ( group >= ULMBCS_DOUBLEOPTGROUP_START ) {
 CHECK_SOURCE_LIMIT ( 2 ) ;
 if ( * args -> source == group ) {
 ++ args -> source ;
 uniChar = ucnv_MBCSSimpleGetNextUChar ( cnv , args -> source , 1 , FALSE ) ;
 ++ args -> source ;
 }
 else {
 uniChar = ucnv_MBCSSimpleGetNextUChar ( cnv , args -> source , 2 , FALSE ) ;
 args -> source += 2 ;
 }
 }
 else {
 CHECK_SOURCE_LIMIT ( 1 ) ;
 CurByte = * ( args -> source ) ++ ;
 if ( CurByte >= ULMBCS_C1START ) {
 uniChar = _MBCS_SINGLE_SIMPLE_GET_NEXT_BMP ( cnv , CurByte ) ;
 }
 else {
 char bytes [ 2 ] ;
 extraInfo = ( UConverterDataLMBCS * ) args -> converter -> extraInfo ;
 cnv = extraInfo -> OptGrpConverter [ ULMBCS_GRP_EXCEPT ] ;
 bytes [ 0 ] = group ;
 bytes [ 1 ] = CurByte ;
 uniChar = ucnv_MBCSSimpleGetNextUChar ( cnv , bytes , 2 , FALSE ) ;
 }
 }
 }
 else if ( CurByte >= ULMBCS_C1START ) {
 extraInfo = ( UConverterDataLMBCS * ) args -> converter -> extraInfo ;
 group = extraInfo -> OptGroup ;
 cnv = extraInfo -> OptGrpConverter [ group ] ;
 if ( group >= ULMBCS_DOUBLEOPTGROUP_START ) {
 if ( ! ucnv_MBCSIsLeadByte ( cnv , CurByte ) ) {
 CHECK_SOURCE_LIMIT ( 0 ) ;
 uniChar = ucnv_MBCSSimpleGetNextUChar ( cnv , args -> source - 1 , 1 , FALSE ) ;
 }
 else {
 CHECK_SOURCE_LIMIT ( 1 ) ;
 uniChar = ucnv_MBCSSimpleGetNextUChar ( cnv , args -> source - 1 , 2 , FALSE ) ;
 ++ args -> source ;
 }
 }
 else {
 uniChar = _MBCS_SINGLE_SIMPLE_GET_NEXT_BMP ( cnv , CurByte ) ;
 }
 }
 }
 return uniChar ;
 }
 static void U_CALLCONV _LMBCSToUnicodeWithOffsets ( UConverterToUnicodeArgs * args , UErrorCode * err ) {
 char LMBCS [ ULMBCS_CHARSIZE_MAX ] ;
 UChar uniChar ;
 const char * saveSource ;
 const char * pStartLMBCS = args -> source ;
 const char * errSource = NULL ;
 int8_t savebytes = 0 ;
 while ( U_SUCCESS ( * err ) && args -> sourceLimit > args -> source && args -> targetLimit > args -> target ) {
 saveSource = args -> source ;
 if ( args -> converter -> toULength ) {
 const char * saveSourceLimit ;
 size_t size_old = args -> converter -> toULength ;
 size_t size_new_maybe_1 = sizeof ( LMBCS ) - size_old ;
 size_t size_new_maybe_2 = args -> sourceLimit - args -> source ;
 size_t size_new = ( size_new_maybe_1 < size_new_maybe_2 ) ? size_new_maybe_1 : size_new_maybe_2 ;
 uprv_memcpy ( LMBCS , args -> converter -> toUBytes , size_old ) ;
 uprv_memcpy ( LMBCS + size_old , args -> source , size_new ) ;
 saveSourceLimit = args -> sourceLimit ;
 args -> source = errSource = LMBCS ;
 args -> sourceLimit = LMBCS + size_old + size_new ;
 savebytes = ( int8_t ) ( size_old + size_new ) ;
 uniChar = ( UChar ) _LMBCSGetNextUCharWorker ( args , err ) ;
 args -> source = saveSource + ( ( args -> source - LMBCS ) - size_old ) ;
 args -> sourceLimit = saveSourceLimit ;
 if ( * err == U_TRUNCATED_CHAR_FOUND ) {
 args -> converter -> toULength = savebytes ;
 uprv_memcpy ( args -> converter -> toUBytes , LMBCS , savebytes ) ;
 args -> source = args -> sourceLimit ;
 * err = U_ZERO_ERROR ;
 return ;
 }
 else {
 args -> converter -> toULength = 0 ;
 }
 }
 else {
 errSource = saveSource ;
 uniChar = ( UChar ) _LMBCSGetNextUCharWorker ( args , err ) ;
 savebytes = ( int8_t ) ( args -> source - saveSource ) ;
 }
 if ( U_SUCCESS ( * err ) ) {
 if ( uniChar < 0xfffe ) {
 * ( args -> target ) ++ = uniChar ;
 if ( args -> offsets ) {
 * ( args -> offsets ) ++ = ( int32_t ) ( saveSource - pStartLMBCS ) ;
 }
 }
 else if ( uniChar == 0xfffe ) {
 * err = U_INVALID_CHAR_FOUND ;
 }
 else {
 * err = U_ILLEGAL_CHAR_FOUND ;
 }
 }
 }
 if ( U_SUCCESS ( * err ) && args -> sourceLimit > args -> source && args -> targetLimit <= args -> target ) {
 * err = U_BUFFER_OVERFLOW_ERROR ;
 }
 else if ( U_FAILURE ( * err ) ) {
 args -> converter -> toULength = savebytes ;
 if ( savebytes > 0 ) {
 uprv_memcpy ( args -> converter -> toUBytes , errSource , savebytes ) ;
 }
 if ( * err == U_TRUNCATED_CHAR_FOUND ) {
 * err = U_ZERO_ERROR ;
 }
 }
 }
 DEFINE_LMBCS_OPEN ( 1 ) DEFINE_LMBCS_OPEN ( 2 ) DEFINE_LMBCS_OPEN ( 3 ) DEFINE_LMBCS_OPEN ( 4 ) DEFINE_LMBCS_OPEN ( 5 ) DEFINE_LMBCS_OPEN ( 6 ) DEFINE_LMBCS_OPEN ( 8 ) DEFINE_LMBCS_OPEN ( 11 ) DEFINE_LMBCS_OPEN ( 16 )