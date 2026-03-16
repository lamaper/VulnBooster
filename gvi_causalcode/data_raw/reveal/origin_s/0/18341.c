Expr * make_opclause ( Oid opno , Oid opresulttype , bool opretset , Expr * leftop , Expr * rightop , Oid opcollid , Oid inputcollid ) {
 OpExpr * expr = makeNode ( OpExpr ) ;
 expr -> opno = opno ;
 expr -> opfuncid = InvalidOid ;
 expr -> opresulttype = opresulttype ;
 expr -> opretset = opretset ;
 expr -> opcollid = opcollid ;
 expr -> inputcollid = inputcollid ;
 if ( rightop ) expr -> args = list_make2 ( leftop , rightop ) ;
 else expr -> args = list_make1 ( leftop ) ;
 expr -> location = - 1 ;
 return ( Expr * ) expr ;
 }