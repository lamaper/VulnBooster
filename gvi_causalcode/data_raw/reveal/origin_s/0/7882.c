static uint32_t U_CALLCONV pointerTOCEntryCount ( const UDataMemory * pData ) {
 const PointerTOC * toc = ( PointerTOC * ) pData -> toc ;
 return ( uint32_t ) ( ( toc != NULL ) ? ( toc -> count ) : 0 ) ;
 }