static int pss_verify_cmp ( void * opaque , gcry_mpi_t tmp ) {
 struct pk_encoding_ctx * ctx = opaque ;
 gcry_mpi_t hash = ctx -> verify_arg ;
 return pss_verify ( hash , tmp , ctx -> nbits - 1 , ctx -> hash_algo , ctx -> saltlen ) ;
 }