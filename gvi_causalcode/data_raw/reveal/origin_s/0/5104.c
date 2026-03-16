gcry_error_t gcry_mpi_scan ( struct gcry_mpi * * ret_mpi , enum gcry_mpi_format format , const void * buffer_arg , size_t buflen , size_t * nscanned ) {
 const unsigned char * buffer = ( const unsigned char * ) buffer_arg ;
 struct gcry_mpi * a = NULL ;
 unsigned int len ;
 int secure = ( buffer && gcry_is_secure ( buffer ) ) ;
 if ( format == GCRYMPI_FMT_SSH ) len = 0 ;
 else len = buflen ;
 if ( format == GCRYMPI_FMT_STD ) {
 const unsigned char * s = buffer ;
 a = secure ? mpi_alloc_secure ( ( len + BYTES_PER_MPI_LIMB - 1 ) / BYTES_PER_MPI_LIMB ) : mpi_alloc ( ( len + BYTES_PER_MPI_LIMB - 1 ) / BYTES_PER_MPI_LIMB ) ;
 if ( len ) {
 a -> sign = ! ! ( * s & 0x80 ) ;
 if ( a -> sign ) {
 mpi_free ( a ) ;
 return gcry_error ( GPG_ERR_INTERNAL ) ;
 }
 else _gcry_mpi_set_buffer ( a , s , len , 0 ) ;
 }
 if ( ret_mpi ) {
 mpi_normalize ( a ) ;
 * ret_mpi = a ;
 }
 else mpi_free ( a ) ;
 return 0 ;
 }
 else if ( format == GCRYMPI_FMT_USG ) {
 a = secure ? mpi_alloc_secure ( ( len + BYTES_PER_MPI_LIMB - 1 ) / BYTES_PER_MPI_LIMB ) : mpi_alloc ( ( len + BYTES_PER_MPI_LIMB - 1 ) / BYTES_PER_MPI_LIMB ) ;
 if ( len ) _gcry_mpi_set_buffer ( a , buffer , len , 0 ) ;
 if ( ret_mpi ) {
 mpi_normalize ( a ) ;
 * ret_mpi = a ;
 }
 else mpi_free ( a ) ;
 return 0 ;
 }
 else if ( format == GCRYMPI_FMT_PGP ) {
 a = mpi_read_from_buffer ( buffer , & len , secure ) ;
 if ( nscanned ) * nscanned = len ;
 if ( ret_mpi && a ) {
 mpi_normalize ( a ) ;
 * ret_mpi = a ;
 }
 else if ( a ) {
 mpi_free ( a ) ;
 a = NULL ;
 }
 return a ? 0 : gcry_error ( GPG_ERR_INV_OBJ ) ;
 }
 else if ( format == GCRYMPI_FMT_SSH ) {
 const unsigned char * s = buffer ;
 size_t n ;
 if ( len && len < 4 ) return gcry_error ( GPG_ERR_TOO_SHORT ) ;
 n = ( s [ 0 ] << 24 | s [ 1 ] << 16 | s [ 2 ] << 8 | s [ 3 ] ) ;
 s += 4 ;
 if ( len ) len -= 4 ;
 if ( len && n > len ) return gcry_error ( GPG_ERR_TOO_LARGE ) ;
 a = secure ? mpi_alloc_secure ( ( n + BYTES_PER_MPI_LIMB - 1 ) / BYTES_PER_MPI_LIMB ) : mpi_alloc ( ( n + BYTES_PER_MPI_LIMB - 1 ) / BYTES_PER_MPI_LIMB ) ;
 if ( n ) {
 a -> sign = ! ! ( * s & 0x80 ) ;
 if ( a -> sign ) {
 mpi_free ( a ) ;
 return gcry_error ( GPG_ERR_INTERNAL ) ;
 }
 else _gcry_mpi_set_buffer ( a , s , n , 0 ) ;
 }
 if ( nscanned ) * nscanned = n + 4 ;
 if ( ret_mpi ) {
 mpi_normalize ( a ) ;
 * ret_mpi = a ;
 }
 else mpi_free ( a ) ;
 return 0 ;
 }
 else if ( format == GCRYMPI_FMT_HEX ) {
 if ( buflen ) return gcry_error ( GPG_ERR_INV_ARG ) ;
 a = secure ? mpi_alloc_secure ( 0 ) : mpi_alloc ( 0 ) ;
 if ( mpi_fromstr ( a , ( const char * ) buffer ) ) {
 mpi_free ( a ) ;
 return gcry_error ( GPG_ERR_INV_OBJ ) ;
 }
 if ( ret_mpi ) {
 mpi_normalize ( a ) ;
 * ret_mpi = a ;
 }
 else mpi_free ( a ) ;
 return 0 ;
 }
 else return gcry_error ( GPG_ERR_INV_ARG ) ;
 }