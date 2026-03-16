static void count_zeroes_and_poles ( uint16_t * LutTable , int length , int * NumZeroes , int * NumPoles ) {
 int z = 0 , p = 0 ;
 while ( LutTable [ z ] == 0 && z < length - 1 ) z ++ ;
 * NumZeroes = z ;
 while ( LutTable [ length - 1 - p ] == 0xFFFF && p < length - 1 ) p ++ ;
 * NumPoles = p ;
 }