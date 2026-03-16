gpg_err_code_t _gcry_mpi_ec_new ( gcry_ctx_t * r_ctx , gcry_sexp_t keyparam , const char * curvename ) {
 gpg_err_code_t errc ;
 gcry_ctx_t ctx = NULL ;
 enum gcry_mpi_ec_models model = MPI_EC_WEIERSTRASS ;
 gcry_mpi_t p = NULL ;
 gcry_mpi_t a = NULL ;
 gcry_mpi_t b = NULL ;
 gcry_mpi_point_t G = NULL ;
 gcry_mpi_t n = NULL ;
 gcry_mpi_point_t Q = NULL ;
 gcry_mpi_t d = NULL ;
 gcry_sexp_t l1 ;
 * r_ctx = NULL ;
 if ( keyparam ) {
 errc = mpi_from_keyparam ( & p , keyparam , "p" ) ;
 if ( errc ) goto leave ;
 errc = mpi_from_keyparam ( & a , keyparam , "a" ) ;
 if ( errc ) goto leave ;
 errc = mpi_from_keyparam ( & b , keyparam , "b" ) ;
 if ( errc ) goto leave ;
 errc = point_from_keyparam ( & G , keyparam , "g" ) ;
 if ( errc ) goto leave ;
 errc = mpi_from_keyparam ( & n , keyparam , "n" ) ;
 if ( errc ) goto leave ;
 errc = point_from_keyparam ( & Q , keyparam , "q" ) ;
 if ( errc ) goto leave ;
 errc = mpi_from_keyparam ( & d , keyparam , "d" ) ;
 if ( errc ) goto leave ;
 }
 if ( keyparam ) l1 = gcry_sexp_find_token ( keyparam , "curve" , 5 ) ;
 else l1 = NULL ;
 if ( l1 || curvename ) {
 char * name ;
 elliptic_curve_t * E ;
 if ( l1 ) {
 name = _gcry_sexp_nth_string ( l1 , 1 ) ;
 gcry_sexp_release ( l1 ) ;
 if ( ! name ) {
 errc = GPG_ERR_INV_OBJ ;
 goto leave ;
 }
 }
 else name = NULL ;
 E = gcry_calloc ( 1 , sizeof * E ) ;
 if ( ! E ) {
 errc = gpg_err_code_from_syserror ( ) ;
 gcry_free ( name ) ;
 goto leave ;
 }
 errc = _gcry_ecc_fill_in_curve ( 0 , name ? name : curvename , E , NULL ) ;
 gcry_free ( name ) ;
 if ( errc ) {
 gcry_free ( E ) ;
 goto leave ;
 }
 model = E -> model ;
 if ( ! p ) {
 p = E -> p ;
 E -> p = NULL ;
 }
 if ( ! a ) {
 a = E -> a ;
 E -> a = NULL ;
 }
 if ( ! b ) {
 b = E -> b ;
 E -> b = NULL ;
 }
 if ( ! G ) {
 G = gcry_mpi_point_snatch_set ( NULL , E -> G . x , E -> G . y , E -> G . z ) ;
 E -> G . x = NULL ;
 E -> G . y = NULL ;
 E -> G . z = NULL ;
 }
 if ( ! n ) {
 n = E -> n ;
 E -> n = NULL ;
 }
 _gcry_ecc_curve_free ( E ) ;
 gcry_free ( E ) ;
 }
 errc = _gcry_mpi_ec_p_new ( & ctx , model , p , a , b ) ;
 if ( ! errc ) {
 mpi_ec_t ec = _gcry_ctx_get_pointer ( ctx , CONTEXT_TYPE_EC ) ;
 if ( b ) {
 ec -> b = b ;
 b = NULL ;
 }
 if ( G ) {
 ec -> G = G ;
 G = NULL ;
 }
 if ( n ) {
 ec -> n = n ;
 n = NULL ;
 }
 if ( Q ) {
 ec -> Q = Q ;
 Q = NULL ;
 }
 if ( d ) {
 ec -> d = d ;
 d = NULL ;
 }
 * r_ctx = ctx ;
 }
 leave : mpi_free ( p ) ;
 mpi_free ( a ) ;
 mpi_free ( b ) ;
 gcry_mpi_point_release ( G ) ;
 mpi_free ( n ) ;
 gcry_mpi_point_release ( Q ) ;
 mpi_free ( d ) ;
 return errc ;
 }