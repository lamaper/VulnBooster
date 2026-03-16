static int search_candidates ( Operation * op , SlapReply * rs , Entry * e , IdScopes * isc , MDB_cursor * mci , ID * ids , ID * stack ) {
 struct mdb_info * mdb = ( struct mdb_info * ) op -> o_bd -> be_private ;
 int rc , depth = 1 ;
 Filter * f , rf , xf , nf , sf ;
 AttributeAssertion aa_ref = ATTRIBUTEASSERTION_INIT ;
 AttributeAssertion aa_subentry = ATTRIBUTEASSERTION_INIT ;
 Debug ( LDAP_DEBUG_TRACE , "search_candidates: base=\"%s\" (0x%08lx) scope=%d\n" , e -> e_nname . bv_val , ( long ) e -> e_id , op -> oq_search . rs_scope ) ;
 f = op -> oq_search . rs_filter ;
 if ( ! oc_filter ( op -> oq_search . rs_filter , 1 , & depth ) && ! get_subentries_visibility ( op ) ) {
 if ( ! get_manageDSAit ( op ) && ! get_domainScope ( op ) ) {
 struct berval bv_ref = BER_BVC ( "referral" ) ;
 rf . f_choice = LDAP_FILTER_EQUALITY ;
 rf . f_ava = & aa_ref ;
 rf . f_av_desc = slap_schema . si_ad_objectClass ;
 rf . f_av_value = bv_ref ;
 rf . f_next = f ;
 xf . f_or = & rf ;
 xf . f_choice = LDAP_FILTER_OR ;
 xf . f_next = NULL ;
 f = & xf ;
 depth ++ ;
 }
 }
 if ( get_subentries_visibility ( op ) ) {
 struct berval bv_subentry = BER_BVC ( "subentry" ) ;
 sf . f_choice = LDAP_FILTER_EQUALITY ;
 sf . f_ava = & aa_subentry ;
 sf . f_av_desc = slap_schema . si_ad_objectClass ;
 sf . f_av_value = bv_subentry ;
 sf . f_next = f ;
 nf . f_choice = LDAP_FILTER_AND ;
 nf . f_and = & sf ;
 nf . f_next = NULL ;
 f = & nf ;
 depth ++ ;
 }
 if ( depth + 1 > mdb -> mi_search_stack_depth ) {
 stack = ch_malloc ( ( depth + 1 ) * MDB_IDL_UM_SIZE * sizeof ( ID ) ) ;
 }
 if ( op -> ors_deref & LDAP_DEREF_SEARCHING ) {
 rc = search_aliases ( op , rs , e -> e_id , isc , mci , stack ) ;
 }
 else {
 rc = LDAP_SUCCESS ;
 }
 if ( rc == LDAP_SUCCESS ) {
 rc = mdb_filter_candidates ( op , isc -> mt , f , ids , stack , stack + MDB_IDL_UM_SIZE ) ;
 }
 if ( depth + 1 > mdb -> mi_search_stack_depth ) {
 ch_free ( stack ) ;
 }
 if ( rc ) {
 Debug ( LDAP_DEBUG_TRACE , "mdb_search_candidates: failed (rc=%d)\n" , rc , NULL , NULL ) ;
 }
 else {
 Debug ( LDAP_DEBUG_TRACE , "mdb_search_candidates: id=%ld first=%ld last=%ld\n" , ( long ) ids [ 0 ] , ( long ) MDB_IDL_FIRST ( ids ) , ( long ) MDB_IDL_LAST ( ids ) ) ;
 }
 return rc ;
 }