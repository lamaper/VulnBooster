const char * _gcry_ecc_get_curve ( gcry_mpi_t * pkey , int iterator , unsigned int * r_nbits ) {
 gpg_err_code_t err ;
 elliptic_curve_t E ;
 int idx ;
 gcry_mpi_t tmp ;
 const char * result = NULL ;
 if ( r_nbits ) * r_nbits = 0 ;
 if ( ! pkey ) {
 idx = iterator ;
 if ( idx >= 0 && idx < DIM ( domain_parms ) ) {
 result = domain_parms [ idx ] . desc ;
 if ( r_nbits ) * r_nbits = domain_parms [ idx ] . nbits ;
 }
 return result ;
 }
 if ( ! pkey [ 0 ] || ! pkey [ 1 ] || ! pkey [ 2 ] || ! pkey [ 3 ] || ! pkey [ 4 ] ) return NULL ;
 E . model = MPI_EC_WEIERSTRASS ;
 E . p = pkey [ 0 ] ;
 E . a = pkey [ 1 ] ;
 E . b = pkey [ 2 ] ;
 _gcry_mpi_point_init ( & E . G ) ;
 err = _gcry_ecc_os2ec ( & E . G , pkey [ 3 ] ) ;
 if ( err ) {
 _gcry_mpi_point_free_parts ( & E . G ) ;
 return NULL ;
 }
 E . n = pkey [ 4 ] ;
 for ( idx = 0 ;
 domain_parms [ idx ] . desc ;
 idx ++ ) {
 tmp = scanval ( domain_parms [ idx ] . p ) ;
 if ( ! mpi_cmp ( tmp , E . p ) ) {
 mpi_free ( tmp ) ;
 tmp = scanval ( domain_parms [ idx ] . a ) ;
 if ( ! mpi_cmp ( tmp , E . a ) ) {
 mpi_free ( tmp ) ;
 tmp = scanval ( domain_parms [ idx ] . b ) ;
 if ( ! mpi_cmp ( tmp , E . b ) ) {
 mpi_free ( tmp ) ;
 tmp = scanval ( domain_parms [ idx ] . n ) ;
 if ( ! mpi_cmp ( tmp , E . n ) ) {
 mpi_free ( tmp ) ;
 tmp = scanval ( domain_parms [ idx ] . g_x ) ;
 if ( ! mpi_cmp ( tmp , E . G . x ) ) {
 mpi_free ( tmp ) ;
 tmp = scanval ( domain_parms [ idx ] . g_y ) ;
 if ( ! mpi_cmp ( tmp , E . G . y ) ) {
 mpi_free ( tmp ) ;
 result = domain_parms [ idx ] . desc ;
 if ( r_nbits ) * r_nbits = domain_parms [ idx ] . nbits ;
 break ;
 }
 }
 }
 }
 }
 }
 mpi_free ( tmp ) ;
 }
 _gcry_mpi_point_free_parts ( & E . G ) ;
 return result ;
 }