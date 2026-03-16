void CommuteRowCompareExpr ( RowCompareExpr * clause ) {
 List * newops ;
 List * temp ;
 ListCell * l ;
 if ( ! IsA ( clause , RowCompareExpr ) ) elog ( ERROR , "expected a RowCompareExpr" ) ;
 newops = NIL ;
 foreach ( l , clause -> opnos ) {
 Oid opoid = lfirst_oid ( l ) ;
 opoid = get_commutator ( opoid ) ;
 if ( ! OidIsValid ( opoid ) ) elog ( ERROR , "could not find commutator for operator %u" , lfirst_oid ( l ) ) ;
 newops = lappend_oid ( newops , opoid ) ;
 }
 switch ( clause -> rctype ) {
 case ROWCOMPARE_LT : clause -> rctype = ROWCOMPARE_GT ;
 break ;
 case ROWCOMPARE_LE : clause -> rctype = ROWCOMPARE_GE ;
 break ;
 case ROWCOMPARE_GE : clause -> rctype = ROWCOMPARE_LE ;
 break ;
 case ROWCOMPARE_GT : clause -> rctype = ROWCOMPARE_LT ;
 break ;
 default : elog ( ERROR , "unexpected RowCompare type: %d" , ( int ) clause -> rctype ) ;
 break ;
 }
 clause -> opnos = newops ;
 temp = clause -> largs ;
 clause -> largs = clause -> rargs ;
 clause -> rargs = temp ;
 }