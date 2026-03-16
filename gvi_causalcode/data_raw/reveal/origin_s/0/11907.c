static sf_count_t psf_get_filelen_fd ( int fd ) {

 if ( fstat64 ( fd , & statbuf ) == - 1 ) return ( sf_count_t ) - 1 ;
 return statbuf . st_size ;

 if ( fstat ( fd , & statbuf ) == - 1 ) return ( sf_count_t ) - 1 ;
 return statbuf . st_size ;
