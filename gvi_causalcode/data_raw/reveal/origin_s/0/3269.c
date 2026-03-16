static Expr * evaluate_function ( Oid funcid , Oid result_type , int32 result_typmod , Oid result_collid , Oid input_collid , List * args , bool funcvariadic , HeapTuple func_tuple , eval_const_expressions_context * context ) {
 Form_pg_proc funcform = ( Form_pg_proc ) GETSTRUCT ( func_tuple ) ;
 bool has_nonconst_input = false ;
 bool has_null_input = false ;
 ListCell * arg ;
 FuncExpr * newexpr ;
 if ( funcform -> proretset ) return NULL ;
 if ( funcform -> prorettype == RECORDOID ) return NULL ;
 foreach ( arg , args ) {
 if ( IsA ( lfirst ( arg ) , Const ) ) has_null_input |= ( ( Const * ) lfirst ( arg ) ) -> constisnull ;
 else has_nonconst_input = true ;
 }
 if ( funcform -> proisstrict && has_null_input ) return ( Expr * ) makeNullConst ( result_type , result_typmod , result_collid ) ;
 if ( has_nonconst_input ) return NULL ;
 if ( funcform -> provolatile == PROVOLATILE_IMMUTABLE ) ;
 else if ( context -> estimate && funcform -> provolatile == PROVOLATILE_STABLE ) ;
 else return NULL ;
 newexpr = makeNode ( FuncExpr ) ;
 newexpr -> funcid = funcid ;
 newexpr -> funcresulttype = result_type ;
 newexpr -> funcretset = false ;
 newexpr -> funcvariadic = funcvariadic ;
 newexpr -> funcformat = COERCE_EXPLICIT_CALL ;
 newexpr -> funccollid = result_collid ;
 newexpr -> inputcollid = input_collid ;
 newexpr -> args = args ;
 newexpr -> location = - 1 ;
 return evaluate_expr ( ( Expr * ) newexpr , result_type , result_typmod , result_collid ) ;
 }