static Entry * deref_base ( Operation * op , SlapReply * rs , Entry * e , Entry * * matched , MDB_txn * txn , ID * tmp , ID * visited ) {
 struct berval ndn ;
 rs -> sr_err = LDAP_ALIAS_DEREF_PROBLEM ;
 rs -> sr_text = "maximum deref depth exceeded" ;
 for ( ;
 ;
 ) {
 * matched = e ;
 if ( MDB_IDL_N ( tmp ) >= op -> o_bd -> be_max_deref_depth ) {
 e = NULL ;
 break ;
 }
 if ( visited && mdb_idl_insert ( visited , e -> e_id ) ) {
 e = NULL ;
 break ;
 }
 if ( mdb_idl_insert ( tmp , e -> e_id ) ) {
 rs -> sr_err = LDAP_ALIAS_PROBLEM ;
 rs -> sr_text = "circular alias" ;
 e = NULL ;
 break ;
 }
 if ( get_alias_dn ( e , & ndn , & rs -> sr_err , & rs -> sr_text ) ) {
 e = NULL ;
 break ;
 }
 rs -> sr_err = mdb_dn2entry ( op , txn , NULL , & ndn , & e , NULL , 0 ) ;
 if ( rs -> sr_err ) {
 rs -> sr_err = LDAP_ALIAS_PROBLEM ;
 rs -> sr_text = "aliasedObject not found" ;
 break ;
 }
 mdb_entry_return ( op , * matched ) ;
 if ( ! is_entry_alias ( e ) ) {
 rs -> sr_err = LDAP_SUCCESS ;
 rs -> sr_text = NULL ;
 break ;
 }
 }
 return e ;
 }