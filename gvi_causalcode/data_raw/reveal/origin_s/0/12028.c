static unsigned char * do_get_buffer ( gcry_mpi_t a , unsigned int fill_le , unsigned int * nbytes , int * sign , int force_secure ) {
 unsigned char * p , * buffer ;
 unsigned int length , tmp ;
 mpi_limb_t alimb ;
 int i ;
 size_t n ;
 if ( sign ) * sign = a -> sign ;
 * nbytes = a -> nlimbs * BYTES_PER_MPI_LIMB ;
 n = * nbytes ? * nbytes : 1 ;
 if ( n < fill_le ) n = fill_le ;
 p = buffer = ( force_secure || mpi_is_secure ( a ) ) ? gcry_malloc_secure ( n ) : gcry_malloc ( n ) ;
 if ( ! buffer ) return NULL ;
 for ( i = a -> nlimbs - 1 ;
 i >= 0 ;
 i -- ) {
 alimb = a -> d [ i ] ;

 * p ++ = alimb >> 16 ;
 * p ++ = alimb >> 8 ;
 * p ++ = alimb ;

 * p ++ = alimb >> 48 ;
 * p ++ = alimb >> 40 ;
 * p ++ = alimb >> 32 ;
 * p ++ = alimb >> 24 ;
 * p ++ = alimb >> 16 ;
 * p ++ = alimb >> 8 ;
 * p ++ = alimb ;

 if ( fill_le ) {
 length = * nbytes ;
 for ( i = 0 ;
 i < length / 2 ;
 i ++ ) {
 tmp = buffer [ i ] ;
 buffer [ i ] = buffer [ length - 1 - i ] ;
 buffer [ length - 1 - i ] = tmp ;
 }
 for ( p = buffer + length ;
 length < fill_le ;
 length ++ ) * p ++ = 0 ;
 * nbytes = length ;
 return buffer ;
 }
 for ( p = buffer ;
 * nbytes && ! * p ;
 p ++ , -- * nbytes ) ;
 if ( p != buffer ) memmove ( buffer , p , * nbytes ) ;
 return buffer ;
 }