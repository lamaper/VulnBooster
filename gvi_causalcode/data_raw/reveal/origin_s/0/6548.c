static int base_candidate ( BackendDB * be , Entry * e , ID * ids ) {
 Debug ( LDAP_DEBUG_ARGS , "base_candidates: base: \"%s\" (0x%08lx)\n" , e -> e_nname . bv_val , ( long ) e -> e_id , 0 ) ;
 ids [ 0 ] = 1 ;
 ids [ 1 ] = e -> e_id ;
 return 0 ;
 }