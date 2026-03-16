List * make_ands_implicit ( Expr * clause ) {
 if ( clause == NULL ) return NIL ;
 else if ( and_clause ( ( Node * ) clause ) ) return ( ( BoolExpr * ) clause ) -> args ;
 else if ( IsA ( clause , Const ) && ! ( ( Const * ) clause ) -> constisnull && DatumGetBool ( ( ( Const * ) clause ) -> constvalue ) ) return NIL ;
 else return list_make1 ( clause ) ;
 }