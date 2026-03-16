static UBool prepareReorder ( const UBiDiLevel * levels , int32_t length , int32_t * indexMap , UBiDiLevel * pMinLevel , UBiDiLevel * pMaxLevel ) {
 int32_t start ;
 UBiDiLevel level , minLevel , maxLevel ;
 if ( levels == NULL || length <= 0 ) {
 return FALSE ;
 }
 minLevel = UBIDI_MAX_EXPLICIT_LEVEL + 1 ;
 maxLevel = 0 ;
 for ( start = length ;
 start > 0 ;
 ) {
 level = levels [ -- start ] ;
 if ( level > UBIDI_MAX_EXPLICIT_LEVEL + 1 ) {
 return FALSE ;
 }
 if ( level < minLevel ) {
 minLevel = level ;
 }
 if ( level > maxLevel ) {
 maxLevel = level ;
 }
 }
 * pMinLevel = minLevel ;
 * pMaxLevel = maxLevel ;
 for ( start = length ;
 start > 0 ;
 ) {
 -- start ;
 indexMap [ start ] = start ;
 }
 return TRUE ;
 }