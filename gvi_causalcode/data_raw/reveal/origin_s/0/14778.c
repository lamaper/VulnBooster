static uint32_t CnvExtWrite ( NewConverter * cnvData , const UConverterStaticData * staticData , UNewDataMemory * pData , int32_t tableType ) {
 CnvExtData * extData = ( CnvExtData * ) cnvData ;
 int32_t length , top , headerSize ;
 int32_t indexes [ UCNV_EXT_INDEXES_MIN_LENGTH ] = {
 0 }
 ;
 if ( tableType & TABLE_BASE ) {
 headerSize = 0 ;
 }
 else {
 _MBCSHeader header = {
 {
 0 , 0 , 0 , 0 }
 , 0 , 0 , 0 , 0 , 0 , 0 , 0 }
 ;
 length = ( int32_t ) uprv_strlen ( extData -> ucm -> baseName ) + 1 ;
 while ( length & 3 ) {
 extData -> ucm -> baseName [ length ++ ] = 0 ;
 }
 headerSize = MBCS_HEADER_V4_LENGTH * 4 + length ;
 header . version [ 0 ] = 4 ;
 header . version [ 1 ] = 2 ;
 header . flags = ( uint32_t ) ( ( headerSize << 8 ) | MBCS_OUTPUT_EXT_ONLY ) ;
 udata_writeBlock ( pData , & header , MBCS_HEADER_V4_LENGTH * 4 ) ;
 udata_writeBlock ( pData , extData -> ucm -> baseName , length ) ;
 }
 top = 0 ;
 indexes [ UCNV_EXT_INDEXES_LENGTH ] = length = UCNV_EXT_INDEXES_MIN_LENGTH ;
 top += length * 4 ;
 indexes [ UCNV_EXT_TO_U_INDEX ] = top ;
 indexes [ UCNV_EXT_TO_U_LENGTH ] = length = utm_countItems ( extData -> toUTable ) ;
 top += length * 4 ;
 indexes [ UCNV_EXT_TO_U_UCHARS_INDEX ] = top ;
 indexes [ UCNV_EXT_TO_U_UCHARS_LENGTH ] = length = utm_countItems ( extData -> toUUChars ) ;
 top += length * 2 ;
 indexes [ UCNV_EXT_FROM_U_UCHARS_INDEX ] = top ;
 length = utm_countItems ( extData -> fromUTableUChars ) ;
 top += length * 2 ;
 if ( top & 3 ) {
 * ( ( UChar * ) utm_alloc ( extData -> fromUTableUChars ) ) = 0 ;
 * ( ( uint32_t * ) utm_alloc ( extData -> fromUTableValues ) ) = 0 ;
 ++ length ;
 top += 2 ;
 }
 indexes [ UCNV_EXT_FROM_U_LENGTH ] = length ;
 indexes [ UCNV_EXT_FROM_U_VALUES_INDEX ] = top ;
 top += length * 4 ;
 indexes [ UCNV_EXT_FROM_U_BYTES_INDEX ] = top ;
 length = utm_countItems ( extData -> fromUBytes ) ;
 top += length ;
 if ( top & 1 ) {
 * ( ( uint8_t * ) utm_alloc ( extData -> fromUBytes ) ) = 0 ;
 ++ length ;
 ++ top ;
 }
 indexes [ UCNV_EXT_FROM_U_BYTES_LENGTH ] = length ;
 indexes [ UCNV_EXT_FROM_U_STAGE_12_INDEX ] = top ;
 indexes [ UCNV_EXT_FROM_U_STAGE_1_LENGTH ] = length = extData -> stage1Top ;
 indexes [ UCNV_EXT_FROM_U_STAGE_12_LENGTH ] = length += extData -> stage2Top ;
 top += length * 2 ;
 indexes [ UCNV_EXT_FROM_U_STAGE_3_INDEX ] = top ;
 length = extData -> stage3Top ;
 top += length * 2 ;
 if ( top & 3 ) {
 extData -> stage3 [ extData -> stage3Top ++ ] = 0 ;
 ++ length ;
 top += 2 ;
 }
 indexes [ UCNV_EXT_FROM_U_STAGE_3_LENGTH ] = length ;
 indexes [ UCNV_EXT_FROM_U_STAGE_3B_INDEX ] = top ;
 indexes [ UCNV_EXT_FROM_U_STAGE_3B_LENGTH ] = length = extData -> stage3bTop ;
 top += length * 4 ;
 indexes [ UCNV_EXT_SIZE ] = top ;
 indexes [ UCNV_EXT_COUNT_BYTES ] = ( extData -> maxInBytes << 16 ) | ( extData -> maxOutBytes << 8 ) | extData -> maxBytesPerUChar ;
 indexes [ UCNV_EXT_COUNT_UCHARS ] = ( extData -> maxInUChars << 16 ) | ( extData -> maxOutUChars << 8 ) | extData -> maxUCharsPerByte ;
 indexes [ UCNV_EXT_FLAGS ] = extData -> ucm -> ext -> unicodeMask ;
 udata_writeBlock ( pData , indexes , sizeof ( indexes ) ) ;
 udata_writeBlock ( pData , utm_getStart ( extData -> toUTable ) , indexes [ UCNV_EXT_TO_U_LENGTH ] * 4 ) ;
 udata_writeBlock ( pData , utm_getStart ( extData -> toUUChars ) , indexes [ UCNV_EXT_TO_U_UCHARS_LENGTH ] * 2 ) ;
 udata_writeBlock ( pData , utm_getStart ( extData -> fromUTableUChars ) , indexes [ UCNV_EXT_FROM_U_LENGTH ] * 2 ) ;
 udata_writeBlock ( pData , utm_getStart ( extData -> fromUTableValues ) , indexes [ UCNV_EXT_FROM_U_LENGTH ] * 4 ) ;
 udata_writeBlock ( pData , utm_getStart ( extData -> fromUBytes ) , indexes [ UCNV_EXT_FROM_U_BYTES_LENGTH ] ) ;
 udata_writeBlock ( pData , extData -> stage1 , extData -> stage1Top * 2 ) ;
 udata_writeBlock ( pData , extData -> stage2 , extData -> stage2Top * 2 ) ;
 udata_writeBlock ( pData , extData -> stage3 , extData -> stage3Top * 2 ) ;
 udata_writeBlock ( pData , extData -> stage3b , extData -> stage3bTop * 4 ) ;

 int32_t i , j ;
 length = extData -> stage1Top ;
 printf ( "\nstage1[%x]:\n" , length ) ;
 for ( i = 0 ;
 i < length ;
 ++ i ) {
 if ( extData -> stage1 [ i ] != length ) {
 printf ( "stage1[%04x]=%04x\n" , i , extData -> stage1 [ i ] ) ;
 }
 }
 j = length ;
 length = extData -> stage2Top ;
 printf ( "\nstage2[%x]:\n" , length ) ;
 for ( i = 0 ;
 i < length ;
 ++ j , ++ i ) {
 if ( extData -> stage2 [ i ] != 0 ) {
 printf ( "stage12[%04x]=%04x\n" , j , extData -> stage2 [ i ] ) ;
 }
 }
 length = extData -> stage3Top ;
 printf ( "\nstage3[%x]:\n" , length ) ;
 for ( i = 0 ;
 i < length ;
 ++ i ) {
 if ( extData -> stage3 [ i ] != 0 ) {
 printf ( "stage3[%04x]=%04x\n" , i , extData -> stage3 [ i ] ) ;
 }
 }
 length = extData -> stage3bTop ;
 printf ( "\nstage3b[%x]:\n" , length ) ;
 for ( i = 0 ;
 i < length ;
 ++ i ) {
 if ( extData -> stage3b [ i ] != 0 ) {
 printf ( "stage3b[%04x]=%08x\n" , i , extData -> stage3b [ i ] ) ;
 }
 }
 }

 printf ( "size of extension data: %ld\n" , ( long ) top ) ;
 }
 return ( uint32_t ) ( headerSize + top ) ;
 }