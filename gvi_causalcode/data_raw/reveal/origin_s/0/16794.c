static gcry_err_code_t sexp_elements_extract_ecc ( gcry_sexp_t key_sexp , const char * element_names , gcry_mpi_t * elements , pk_extra_spec_t * extraspec , int want_private ) {
 gcry_err_code_t err = 0 ;
 int idx ;
 const char * name ;
 gcry_sexp_t list ;
 for ( name = element_names , idx = 0 ;
 * name ;
 name ++ , idx ++ ) elements [ idx ] = NULL ;
 gcry_assert ( idx >= 5 ) ;
 if ( idx == 5 ) elements [ 5 ] = NULL ;
 for ( name = element_names , idx = 0 ;
 * name && ! err ;
 name ++ , idx ++ ) {
 list = gcry_sexp_find_token ( key_sexp , name , 1 ) ;
 if ( ! list ) elements [ idx ] = NULL ;
 else {
 elements [ idx ] = gcry_sexp_nth_mpi ( list , 1 , GCRYMPI_FMT_USG ) ;
 gcry_sexp_release ( list ) ;
 if ( ! elements [ idx ] ) {
 err = GPG_ERR_INV_OBJ ;
 goto leave ;
 }
 }
 }
 list = gcry_sexp_find_token ( key_sexp , "curve" , 5 ) ;
 if ( list ) {
 if ( extraspec -> get_param ) {
 char * curve ;
 gcry_mpi_t params [ 6 ] ;
 for ( idx = 0 ;
 idx < DIM ( params ) ;
 idx ++ ) params [ idx ] = NULL ;
 curve = _gcry_sexp_nth_string ( list , 1 ) ;
 gcry_sexp_release ( list ) ;
 if ( ! curve ) {
 err = GPG_ERR_INV_OBJ ;
 goto leave ;
 }
 err = extraspec -> get_param ( curve , params ) ;
 gcry_free ( curve ) ;
 if ( err ) goto leave ;
 for ( idx = 0 ;
 idx < DIM ( params ) ;
 idx ++ ) {
 if ( ! elements [ idx ] ) elements [ idx ] = params [ idx ] ;
 else mpi_free ( params [ idx ] ) ;
 }
 }
 else {
 gcry_sexp_release ( list ) ;
 err = GPG_ERR_INV_OBJ ;
 goto leave ;
 }
 }
 for ( name = element_names , idx = 0 ;
 * name ;
 name ++ , idx ++ ) if ( ! elements [ idx ] ) {
 if ( want_private && * name == 'q' ) ;
 else {
 err = GPG_ERR_NO_OBJ ;
 goto leave ;
 }
 }
 leave : if ( err ) {
 for ( name = element_names , idx = 0 ;
 * name ;
 name ++ , idx ++ ) if ( elements [ idx ] ) mpi_free ( elements [ idx ] ) ;
 }
 return err ;
 }