static UChar32 _LMBCSGetNextUCharWorker ( UConverterToUnicodeArgs * args , UErrorCode * err ) {
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