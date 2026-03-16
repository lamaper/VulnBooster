byte * _gcry_mpi_get_buffer ( gcry_mpi_t a , unsigned int fill_le , unsigned int * r_nbytes , int * sign ) {
 return do_get_buffer ( a , fill_le , r_nbytes , sign , 0 ) ;
 }