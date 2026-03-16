static UBool makeFromUTable ( CnvExtData * extData , UCMTable * table ) {
 uint16_t * stage1 ;
 int32_t i , stage1Top , fromUCount ;
 fromUCount = prepareFromUMappings ( table ) ;
 extData -> fromUTableUChars = utm_open ( "cnv extension fromUTableUChars" , 0x10000 , UCNV_EXT_FROM_U_DATA_MASK + 1 , 2 ) ;
 extData -> fromUTableValues = utm_open ( "cnv extension fromUTableValues" , 0x10000 , UCNV_EXT_FROM_U_DATA_MASK + 1 , 4 ) ;
 extData -> fromUBytes = utm_open ( "cnv extension fromUBytes" , 0x10000 , UCNV_EXT_FROM_U_DATA_MASK + 1 , 1 ) ;
 extData -> stage2Top = MBCS_STAGE_2_FIRST_ASSIGNED ;
 extData -> stage3Top = MBCS_STAGE_3_FIRST_ASSIGNED ;
 extData -> stage3b [ 1 ] = UCNV_EXT_FROM_U_SUBCHAR1 ;
 extData -> stage3bTop = 2 ;
 utm_alloc ( extData -> fromUTableUChars ) ;
 utm_alloc ( extData -> fromUTableValues ) ;
 if ( ! generateFromUTrie ( extData , table , fromUCount ) ) {
 return FALSE ;
 }
 stage1 = extData -> stage1 ;
 stage1Top = extData -> stage1Top ;
 for ( i = 0 ;
 i < stage1Top ;
 ++ i ) {
 stage1 [ i ] = ( uint16_t ) ( stage1 [ i ] + stage1Top ) ;
 }
 return TRUE ;
 }