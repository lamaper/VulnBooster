static UBool generateFromUTable ( CnvExtData * extData , UCMTable * table , int32_t start , int32_t limit , int32_t unitIndex , uint32_t defaultValue ) {
 UCMapping * mappings , * m ;
 int32_t * map ;
 int32_t i , j , uniqueCount , count , subStart , subLimit ;
 UChar * uchars ;
 UChar32 low , high , prev ;
 UChar * sectionUChars ;
 uint32_t * sectionValues ;
 mappings = table -> mappings ;
 map = table -> reverseMap ;
 m = mappings + map [ start ] ;
 uchars = ( UChar * ) UCM_GET_CODE_POINTS ( table , m ) ;
 low = uchars [ unitIndex ] ;
 uniqueCount = 1 ;
 prev = high = low ;
 for ( i = start + 1 ;
 i < limit ;
 ++ i ) {
 m = mappings + map [ i ] ;
 uchars = ( UChar * ) UCM_GET_CODE_POINTS ( table , m ) ;
 high = uchars [ unitIndex ] ;
 if ( high != prev ) {
 prev = high ;
 ++ uniqueCount ;
 }
 }
 count = uniqueCount ;
 sectionUChars = ( UChar * ) utm_allocN ( extData -> fromUTableUChars , 1 + count ) ;
 sectionValues = ( uint32_t * ) utm_allocN ( extData -> fromUTableValues , 1 + count ) ;
 * sectionUChars ++ = ( UChar ) count ;
 * sectionValues ++ = defaultValue ;
 prev = low - 1 ;
 j = 0 ;
 for ( i = start ;
 i < limit ;
 ++ i ) {
 m = mappings + map [ i ] ;
 uchars = ( UChar * ) UCM_GET_CODE_POINTS ( table , m ) ;
 high = uchars [ unitIndex ] ;
 if ( high != prev ) {
 prev = high ;
 sectionUChars [ j ] = ( UChar ) high ;
 sectionValues [ j ] = ( uint32_t ) i ;
 ++ j ;
 }
 }
 subLimit = ( int32_t ) ( sectionValues [ 0 ] ) ;
 for ( j = 0 ;
 j < count ;
 ++ j ) {
 subStart = subLimit ;
 subLimit = ( j + 1 ) < count ? ( int32_t ) ( sectionValues [ j + 1 ] ) : limit ;
 defaultValue = 0 ;
 m = mappings + map [ subStart ] ;
 if ( m -> uLen == unitIndex + 1 ) {
 ++ subStart ;
 if ( subStart < subLimit && mappings [ map [ subStart ] ] . uLen == unitIndex + 1 ) {
 fprintf ( stderr , "error: multiple mappings from same Unicode code points\n" ) ;
 ucm_printMapping ( table , m , stderr ) ;
 ucm_printMapping ( table , mappings + map [ subStart ] , stderr ) ;
 return FALSE ;
 }
 defaultValue = getFromUBytesValue ( extData , table , m ) ;
 }
 if ( subStart == subLimit ) {
 sectionValues [ j ] = defaultValue ;
 }
 else {
 sectionValues [ j ] = ( uint32_t ) utm_countItems ( extData -> fromUTableValues ) ;
 if ( ! generateFromUTable ( extData , table , subStart , subLimit , unitIndex + 1 , defaultValue ) ) {
 return FALSE ;
 }
 }
 }
 return TRUE ;
 }