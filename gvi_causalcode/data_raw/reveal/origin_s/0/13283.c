static void print_point ( const char * text , gcry_mpi_point_t a ) {
 gcry_mpi_t x , y , z ;
 x = gcry_mpi_new ( 0 ) ;
 y = gcry_mpi_new ( 0 ) ;
 z = gcry_mpi_new ( 0 ) ;
 gcry_mpi_point_get ( x , y , z , a ) ;
 print_mpi_2 ( text , ".x" , x ) ;
 print_mpi_2 ( text , ".y" , y ) ;
 print_mpi_2 ( text , ".z" , z ) ;
 gcry_mpi_release ( x ) ;
 gcry_mpi_release ( y ) ;
 gcry_mpi_release ( z ) ;
 }