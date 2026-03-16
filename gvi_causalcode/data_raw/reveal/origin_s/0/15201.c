static UBool generateFromUTrie ( CnvExtData * extData , UCMTable * table , int32_t mapLength ) {
 UCMapping * mappings , * m ;
 int32_t * map ;
 uint32_t value ;
 int32_t subStart , subLimit ;
 UChar32 * codePoints ;
 UChar32 c , next ;
 if ( mapLength == 0 ) {
 return TRUE ;
 }
 mappings = table -> mappings ;
 map = table -> reverseMap ;
 m = mappings + map [ 0 ] ;
 codePoints = UCM_GET_CODE_POINTS ( table , m ) ;
 next = codePoints [ 0 ] ;
 subLimit = 0 ;
 while ( subLimit < mapLength ) {
 subStart = subLimit ;
 c = next ;
 while ( next == c && ++ subLimit < mapLength ) {
 m = mappings + map [ subLimit ] ;
 codePoints = UCM_GET_CODE_POINTS ( table , m ) ;
 next = codePoints [ 0 ] ;
 }
 value = 0 ;
 m = mappings + map [ subStart ] ;
 codePoints = UCM_GET_CODE_POINTS ( table , m ) ;
 if ( m -> uLen == 1 ) {
 ++ subStart ;
 if ( subStart < subLimit && mappings [ map [ subStart ] ] . uLen == 1 ) {
 fprintf ( stderr , "error: multiple mappings from same Unicode code points\n" ) ;
 ucm_printMapping ( table , m , stderr ) ;
 ucm_printMapping ( table , mappings + map [ subStart ] , stderr ) ;
 return FALSE ;
 }
 value = getFromUBytesValue ( extData , table , m ) ;
 }
 if ( subStart == subLimit ) {
 addFromUTrieEntry ( extData , c , value ) ;
 }
 else {
 addFromUTrieEntry ( extData , c , ( uint32_t ) utm_countItems ( extData -> fromUTableValues ) ) ;
 if ( ! generateFromUTable ( extData , table , subStart , subLimit , 2 , value ) ) {
 return FALSE ;
 }
 }
 }
 return TRUE ;
 }