static int search_aliases ( Operation * op , SlapReply * rs , ID e_id , IdScopes * isc , MDB_cursor * mci , ID * stack ) {
 ID * aliases , * curscop , * visited , * newsubs , * oldsubs , * tmp ;
 ID cursora , ida , cursoro , ido ;
 Entry * matched , * a ;
 struct berval bv_alias = BER_BVC ( "alias" ) ;
 AttributeAssertion aa_alias = ATTRIBUTEASSERTION_INIT ;
 Filter af ;
 aliases = stack ;
 curscop = aliases + MDB_IDL_DB_SIZE ;
 visited = curscop + MDB_IDL_DB_SIZE ;
 newsubs = visited + MDB_IDL_DB_SIZE ;
 oldsubs = newsubs + MDB_IDL_DB_SIZE ;
 tmp = oldsubs + MDB_IDL_DB_SIZE ;
 af . f_choice = LDAP_FILTER_EQUALITY ;
 af . f_ava = & aa_alias ;
 af . f_av_desc = slap_schema . si_ad_objectClass ;
 af . f_av_value = bv_alias ;
 af . f_next = NULL ;
 MDB_IDL_ZERO ( aliases ) ;
 rs -> sr_err = mdb_filter_candidates ( op , isc -> mt , & af , aliases , curscop , visited ) ;
 if ( rs -> sr_err != LDAP_SUCCESS || MDB_IDL_IS_ZERO ( aliases ) ) {
 return rs -> sr_err ;
 }
 oldsubs [ 0 ] = 1 ;
 oldsubs [ 1 ] = e_id ;
 MDB_IDL_ZERO ( visited ) ;
 MDB_IDL_ZERO ( newsubs ) ;
 cursoro = 0 ;
 ido = mdb_idl_first ( oldsubs , & cursoro ) ;
 for ( ;
 ;
 ) {
 rs -> sr_err = mdb_idscope ( op , isc -> mt , e_id , aliases , curscop ) ;
 cursora = 0 ;
 for ( ida = mdb_idl_first ( curscop , & cursora ) ;
 ida != NOID ;
 ida = mdb_idl_next ( curscop , & cursora ) ) {
 rs -> sr_err = mdb_id2entry ( op , mci , ida , & a ) ;
 if ( rs -> sr_err != LDAP_SUCCESS ) {
 continue ;
 }
 if ( ! is_entry_alias ( a ) ) {
 mdb_entry_return ( op , a ) ;
 continue ;
 }
 MDB_IDL_ZERO ( tmp ) ;
 a = deref_base ( op , rs , a , & matched , isc -> mt , tmp , visited ) ;
 if ( a ) {
 ID2 mid ;
 mid . mid = a -> e_id ;
 mid . mval . mv_data = NULL ;
 if ( op -> ors_scope == LDAP_SCOPE_SUBTREE ) {
 isc -> id = a -> e_id ;
 if ( mdb_idscopechk ( op , isc ) ) goto skip ;
 }
 if ( mdb_id2l_insert ( isc -> scopes , & mid ) == 0 ) {
 mdb_idl_insert ( newsubs , a -> e_id ) ;
 }
 skip : mdb_entry_return ( op , a ) ;
 }
 else if ( matched ) {
 mdb_entry_return ( op , matched ) ;
 rs -> sr_text = NULL ;
 rs -> sr_err = 0 ;
 }
 }
 if ( op -> ors_scope == LDAP_SCOPE_ONELEVEL ) break ;
 nextido : ido = mdb_idl_next ( oldsubs , & cursoro ) ;
 if ( ido == NOID ) {
 if ( MDB_IDL_IS_ZERO ( newsubs ) ) break ;
 MDB_IDL_CPY ( oldsubs , newsubs ) ;
 MDB_IDL_ZERO ( newsubs ) ;
 cursoro = 0 ;
 ido = mdb_idl_first ( oldsubs , & cursoro ) ;
 }
 {
 MDB_val edata ;
 rs -> sr_err = mdb_id2edata ( op , mci , ido , & edata ) ;
 if ( rs -> sr_err != MDB_SUCCESS ) {
 goto nextido ;
 }
 e_id = ido ;
 }
 }
 return rs -> sr_err ;
 }