Selectivity rowcomparesel ( PlannerInfo * root , RowCompareExpr * clause , int varRelid , JoinType jointype , SpecialJoinInfo * sjinfo ) {
 Selectivity s1 ;
 Oid opno = linitial_oid ( clause -> opnos ) ;
 Oid inputcollid = linitial_oid ( clause -> inputcollids ) ;
 List * opargs ;
 bool is_join_clause ;
 opargs = list_make2 ( linitial ( clause -> largs ) , linitial ( clause -> rargs ) ) ;
 if ( varRelid != 0 ) {
 is_join_clause = false ;
 }
 else if ( sjinfo == NULL ) {
 is_join_clause = false ;
 }
 else {
 is_join_clause = ( NumRelids ( ( Node * ) opargs ) > 1 ) ;
 }
 if ( is_join_clause ) {
 s1 = join_selectivity ( root , opno , opargs , inputcollid , jointype , sjinfo ) ;
 }
 else {
 s1 = restriction_selectivity ( root , opno , opargs , inputcollid , varRelid ) ;
 }
 return s1 ;
 }