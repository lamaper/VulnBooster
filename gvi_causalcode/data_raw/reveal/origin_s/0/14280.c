static int32_t prepareFromUMappings ( UCMTable * table ) {
 UCMapping * mappings , * m ;
 int32_t * map ;
 int32_t i , j , count ;
 int8_t flag ;
 mappings = table -> mappings ;
 map = table -> reverseMap ;
 count = table -> mappingsLength ;
 m = mappings ;
 for ( i = j = 0 ;
 i < count ;
 ++ m , ++ i ) {
 flag = m -> f ;
 if ( flag >= 0 ) {
 flag &= MBCS_FROM_U_EXT_MASK ;
 m -> f = flag ;
 }
 if ( flag == 0 || flag == 1 || ( flag == 2 && m -> bLen == 1 ) || flag == 4 ) {
 map [ j ++ ] = i ;
 if ( m -> uLen > 1 ) {
 UChar32 * u32 ;
 UChar * u ;
 UChar32 c ;
 int32_t q , r ;
 u32 = UCM_GET_CODE_POINTS ( table , m ) ;
 u = ( UChar * ) u32 ;
 for ( r = 2 , q = 1 ;
 q < m -> uLen ;
 ++ q ) {
 c = u32 [ q ] ;
 U16_APPEND_UNSAFE ( u , r , c ) ;
 }
 m -> uLen = ( int8_t ) r ;
 }
 }
 }
 return j ;
 }