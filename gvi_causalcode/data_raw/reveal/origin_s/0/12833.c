const char * gcry_sexp_nth_data ( const gcry_sexp_t list , int number , size_t * datalen ) {
 return sexp_nth_data ( list , number , datalen ) ;
 }