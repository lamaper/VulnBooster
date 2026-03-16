static int32_t reduceToUMappings ( UCMTable * table ) {
 UCMapping * mappings ;
 int32_t * map ;
 int32_t i , j , count ;
 int8_t flag ;
 mappings = table -> mappings ;
 map = table -> reverseMap ;
 count = table -> mappingsLength ;
 for ( i = j = 0 ;
 i < count ;
 ++ i ) {
 flag = mappings [ map [ i ] ] . f ;
 if ( flag != 0 && flag != 3 ) {
 break ;
 }
 }
 for ( j = i ;
 i < count ;
 ++ i ) {
 flag = mappings [ map [ i ] ] . f ;
 if ( flag == 0 || flag == 3 ) {
 map [ j ++ ] = map [ i ] ;
 }
 }
 return j ;
 }