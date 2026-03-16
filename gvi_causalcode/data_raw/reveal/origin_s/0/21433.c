static int floor_log2 ( uint32 n ) {
 int logval = 0 ;
 if ( n == 0 ) return - 1 ;
 if ( n >= ( 1 << 16 ) ) {
 n >>= 16 ;
 logval += 16 ;
 }
 if ( n >= ( 1 << 8 ) ) {
 n >>= 8 ;
 logval += 8 ;
 }
 if ( n >= ( 1 << 4 ) ) {
 n >>= 4 ;
 logval += 4 ;
 }
 if ( n >= ( 1 << 2 ) ) {
 n >>= 2 ;
 logval += 2 ;
 }
 if ( n >= ( 1 << 1 ) ) {
 logval += 1 ;
 }
 return logval ;
 }