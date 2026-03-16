gcry_sexp_t gcry_sexp_cadr ( const gcry_sexp_t list ) {
 gcry_sexp_t a , b ;
 a = gcry_sexp_cdr ( list ) ;
 b = gcry_sexp_car ( a ) ;
 gcry_sexp_release ( a ) ;
 return b ;
 }