static UBool generateToUTable ( CnvExtData * extData , UCMTable * table , int32_t start , int32_t limit , int32_t unitIndex , uint32_t defaultValue ) {
 UCMapping * mappings , * m ;
 int32_t * map ;
 int32_t i , j , uniqueCount , count , subStart , subLimit ;
 uint8_t * bytes ;
 int32_t low , high , prev ;
 uint32_t * section ;
 mappings = table -> mappings ;
 map = table -> reverseMap ;
 m = mappings + map [ start ] ;
 bytes = UCM_GET_BYTES ( table , m ) ;
 low = bytes [ unitIndex ] ;
 uniqueCount = 1 ;
 prev = high = low ;
 for ( i = start + 1 ;
 i < limit ;
 ++ i ) {
 m = mappings + map [ i ] ;
 bytes = UCM_GET_BYTES ( table , m ) ;
 high = bytes [ unitIndex ] ;
 if ( high != prev ) {
 prev = high ;
 ++ uniqueCount ;
 }
 }
 count = ( high - low ) + 1 ;
 if ( count < 0x100 && ( unitIndex == 0 || uniqueCount >= ( 3 * count ) / 4 ) ) {
 }
 else {
 count = uniqueCount ;
 }
 if ( count >= 0x100 ) {
 fprintf ( stderr , "error: toUnicode extension table section overflow: %ld section entries\n" , ( long ) count ) ;
 return FALSE ;
 }
 section = ( uint32_t * ) utm_allocN ( extData -> toUTable , 1 + count ) ;
 * section ++ = ( ( uint32_t ) count << UCNV_EXT_TO_U_BYTE_SHIFT ) | defaultValue ;
 prev = low - 1 ;
 j = 0 ;
 for ( i = start ;
 i < limit ;
 ++ i ) {
 m = mappings + map [ i ] ;
 bytes = UCM_GET_BYTES ( table , m ) ;
 high = bytes [ unitIndex ] ;
 if ( high != prev ) {
 if ( count > uniqueCount ) {
 while ( ++ prev < high ) {
 section [ j ++ ] = ( ( uint32_t ) prev << UCNV_EXT_TO_U_BYTE_SHIFT ) | ( uint32_t ) i ;
 }
 }
 else {
 prev = high ;
 }
 section [ j ++ ] = ( ( uint32_t ) high << UCNV_EXT_TO_U_BYTE_SHIFT ) | ( uint32_t ) i ;
 }
 }
 subLimit = UCNV_EXT_TO_U_GET_VALUE ( section [ 0 ] ) ;
 for ( j = 0 ;
 j < count ;
 ++ j ) {
 subStart = subLimit ;
 subLimit = ( j + 1 ) < count ? UCNV_EXT_TO_U_GET_VALUE ( section [ j + 1 ] ) : limit ;
 section [ j ] &= ~ UCNV_EXT_TO_U_VALUE_MASK ;
 if ( subStart == subLimit ) {
 continue ;
 }
 defaultValue = 0 ;
 m = mappings + map [ subStart ] ;
 if ( m -> bLen == unitIndex + 1 ) {
 ++ subStart ;
 if ( subStart < subLimit && mappings [ map [ subStart ] ] . bLen == unitIndex + 1 ) {
 fprintf ( stderr , "error: multiple mappings from same bytes\n" ) ;
 ucm_printMapping ( table , m , stderr ) ;
 ucm_printMapping ( table , mappings + map [ subStart ] , stderr ) ;
 return FALSE ;
 }
 defaultValue = getToUnicodeValue ( extData , table , m ) ;
 }
 if ( subStart == subLimit ) {
 section [ j ] |= defaultValue ;
 }
 else {
 section [ j ] |= ( uint32_t ) utm_countItems ( extData -> toUTable ) ;
 if ( ! generateToUTable ( extData , table , subStart , subLimit , unitIndex + 1 , defaultValue ) ) {
 return FALSE ;
 }
 }
 }
 return TRUE ;
 }