void CommuteOpExpr ( OpExpr * clause ) {
 Oid opoid ;
 Node * temp ;
 if ( ! is_opclause ( clause ) || list_length ( clause -> args ) != 2 ) elog ( ERROR , "cannot commute non-binary-operator clause" ) ;
 opoid = get_commutator ( clause -> opno ) ;
 if ( ! OidIsValid ( opoid ) ) elog ( ERROR , "could not find commutator for operator %u" , clause -> opno ) ;
 clause -> opno = opoid ;
 clause -> opfuncid = InvalidOid ;
 temp = linitial ( clause -> args ) ;
 linitial ( clause -> args ) = lsecond ( clause -> args ) ;
 lsecond ( clause -> args ) = temp ;
 }