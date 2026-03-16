static void addFromUTrieEntry ( CnvExtData * extData , UChar32 c , uint32_t value ) {
 int32_t i1 , i2 , i3 , i3b , nextOffset , min , newBlock ;
 if ( value == 0 ) {
 return ;
 }
 i1 = c >> 10 ;
 if ( i1 >= extData -> stage1Top ) {
 extData -> stage1Top = i1 + 1 ;
 }
 nextOffset = ( c >> 4 ) & 0x3f ;
 if ( extData -> stage1 [ i1 ] == 0 ) {
 newBlock = extData -> stage2Top ;
 min = newBlock - nextOffset ;
 while ( min < newBlock && extData -> stage2 [ newBlock - 1 ] == 0 ) {
 -- newBlock ;
 }
 extData -> stage1 [ i1 ] = ( uint16_t ) newBlock ;
 extData -> stage2Top = newBlock + MBCS_STAGE_2_BLOCK_SIZE ;
 if ( extData -> stage2Top > UPRV_LENGTHOF ( extData -> stage2 ) ) {
 fprintf ( stderr , "error: too many stage 2 entries at U+%04x\n" , ( int ) c ) ;
 exit ( U_MEMORY_ALLOCATION_ERROR ) ;
 }
 }
 i2 = extData -> stage1 [ i1 ] + nextOffset ;
 nextOffset = c & 0xf ;
 if ( extData -> stage2 [ i2 ] == 0 ) {
 newBlock = extData -> stage3Top ;
 min = newBlock - nextOffset ;
 while ( min < newBlock && extData -> stage3 [ newBlock - 1 ] == 0 ) {
 -- newBlock ;
 }
 newBlock = ( newBlock + ( UCNV_EXT_STAGE_3_GRANULARITY - 1 ) ) & ~ ( UCNV_EXT_STAGE_3_GRANULARITY - 1 ) ;
 extData -> stage2 [ i2 ] = ( uint16_t ) ( newBlock >> UCNV_EXT_STAGE_2_LEFT_SHIFT ) ;
 extData -> stage3Top = newBlock + MBCS_STAGE_3_BLOCK_SIZE ;
 if ( extData -> stage3Top > UPRV_LENGTHOF ( extData -> stage3 ) ) {
 fprintf ( stderr , "error: too many stage 3 entries at U+%04x\n" , ( int ) c ) ;
 exit ( U_MEMORY_ALLOCATION_ERROR ) ;
 }
 }
 i3 = ( ( int32_t ) extData -> stage2 [ i2 ] << UCNV_EXT_STAGE_2_LEFT_SHIFT ) + nextOffset ;
 if ( value == UCNV_EXT_FROM_U_SUBCHAR1 ) {
 extData -> stage3 [ i3 ] = 1 ;
 if ( nextOffset == MBCS_STAGE_3_BLOCK_SIZE - 1 ) {
 for ( min = i3 - nextOffset ;
 min < i3 && extData -> stage3 [ min ] == 1 ;
 ++ min ) {
 }
 if ( min == i3 ) {
 if ( extData -> stage3Sub1Block != 0 ) {
 extData -> stage2 [ i2 ] = extData -> stage3Sub1Block ;
 extData -> stage3Top -= MBCS_STAGE_3_BLOCK_SIZE ;
 uprv_memset ( extData -> stage3 + extData -> stage3Top , 0 , MBCS_STAGE_3_BLOCK_SIZE * 2 ) ;
 }
 else {
 extData -> stage3Sub1Block = extData -> stage2 [ i2 ] ;
 }
 }
 }
 }
 else {
 if ( ( i3b = extData -> stage3bTop ++ ) >= UPRV_LENGTHOF ( extData -> stage3b ) ) {
 fprintf ( stderr , "error: too many stage 3b entries at U+%04x\n" , ( int ) c ) ;
 exit ( U_MEMORY_ALLOCATION_ERROR ) ;
 }
 extData -> stage3 [ i3 ] = ( uint16_t ) i3b ;
 extData -> stage3b [ i3b ] = value ;
 }
 }