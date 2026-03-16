void vp8_plane_add_noise_c ( unsigned char * Start , char * noise , char blackclamp [ 16 ] , char whiteclamp [ 16 ] , char bothclamp [ 16 ] , unsigned int Width , unsigned int Height , int Pitch ) {
 unsigned int i , j ;
 for ( i = 0 ;
 i < Height ;
 i ++ ) {
 unsigned char * Pos = Start + i * Pitch ;
 char * Ref = ( char * ) ( noise + ( rand ( ) & 0xff ) ) ;
 for ( j = 0 ;
 j < Width ;
 j ++ ) {
 if ( Pos [ j ] < blackclamp [ 0 ] ) Pos [ j ] = blackclamp [ 0 ] ;
 if ( Pos [ j ] > 255 + whiteclamp [ 0 ] ) Pos [ j ] = 255 + whiteclamp [ 0 ] ;
 Pos [ j ] += Ref [ j ] ;
 }
 }
 }