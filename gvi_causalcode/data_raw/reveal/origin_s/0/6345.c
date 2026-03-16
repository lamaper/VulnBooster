static int mpi_fromstr ( gcry_mpi_t val , const char * str ) {
 int sign = 0 ;
 int prepend_zero = 0 ;
 int i , j , c , c1 , c2 ;
 unsigned int nbits , nbytes , nlimbs ;
 mpi_limb_t a ;
 if ( * str == '-' ) {
 sign = 1 ;
 str ++ ;
 }
 if ( * str == '0' && str [ 1 ] == 'x' ) str += 2 ;
 nbits = 4 * strlen ( str ) ;
 if ( ( nbits % 8 ) ) prepend_zero = 1 ;
 nbytes = ( nbits + 7 ) / 8 ;
 nlimbs = ( nbytes + BYTES_PER_MPI_LIMB - 1 ) / BYTES_PER_MPI_LIMB ;
 if ( val -> alloced < nlimbs ) mpi_resize ( val , nlimbs ) ;
 i = BYTES_PER_MPI_LIMB - ( nbytes % BYTES_PER_MPI_LIMB ) ;
 i %= BYTES_PER_MPI_LIMB ;
 j = val -> nlimbs = nlimbs ;
 val -> sign = sign ;
 for ( ;
 j > 0 ;
 j -- ) {
 a = 0 ;
 for ( ;
 i < BYTES_PER_MPI_LIMB ;
 i ++ ) {
 if ( prepend_zero ) {
 c1 = '0' ;
 prepend_zero = 0 ;
 }
 else c1 = * str ++ ;
 if ( ! c1 ) {
 mpi_clear ( val ) ;
 return 1 ;
 }
 c2 = * str ++ ;
 if ( ! c2 ) {
 mpi_clear ( val ) ;
 return 1 ;
 }
 if ( c1 >= '0' && c1 <= '9' ) c = c1 - '0' ;
 else if ( c1 >= 'a' && c1 <= 'f' ) c = c1 - 'a' + 10 ;
 else if ( c1 >= 'A' && c1 <= 'F' ) c = c1 - 'A' + 10 ;
 else {
 mpi_clear ( val ) ;
 return 1 ;
 }
 c <<= 4 ;
 if ( c2 >= '0' && c2 <= '9' ) c |= c2 - '0' ;
 else if ( c2 >= 'a' && c2 <= 'f' ) c |= c2 - 'a' + 10 ;
 else if ( c2 >= 'A' && c2 <= 'F' ) c |= c2 - 'A' + 10 ;
 else {
 mpi_clear ( val ) ;
 return 1 ;
 }
 a <<= 8 ;
 a |= c ;
 }
 i = 0 ;
 val -> d [ j - 1 ] = a ;
 }
 return 0 ;
 }