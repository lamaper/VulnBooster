static int cmp_mpihex ( gcry_mpi_t a , const char * b ) {
 gcry_mpi_t bval ;
 int res ;
 bval = hex2mpi ( b ) ;
 res = gcry_mpi_cmp ( a , bval ) ;
 gcry_mpi_release ( bval ) ;
 return res ;
 }