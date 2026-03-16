static Expr * evaluate_expr ( Expr * expr , Oid result_type , int32 result_typmod , Oid result_collation ) {
 EState * estate ;
 ExprState * exprstate ;
 MemoryContext oldcontext ;
 Datum const_val ;
 bool const_is_null ;
 int16 resultTypLen ;
 bool resultTypByVal ;
 estate = CreateExecutorState ( ) ;
 oldcontext = MemoryContextSwitchTo ( estate -> es_query_cxt ) ;
 fix_opfuncids ( ( Node * ) expr ) ;
 exprstate = ExecInitExpr ( expr , NULL ) ;
 const_val = ExecEvalExprSwitchContext ( exprstate , GetPerTupleExprContext ( estate ) , & const_is_null , NULL ) ;
 get_typlenbyval ( result_type , & resultTypLen , & resultTypByVal ) ;
 MemoryContextSwitchTo ( oldcontext ) ;
 if ( ! const_is_null ) {
 if ( resultTypLen == - 1 ) const_val = PointerGetDatum ( PG_DETOAST_DATUM_COPY ( const_val ) ) ;
 else const_val = datumCopy ( const_val , resultTypByVal , resultTypLen ) ;
 }
 FreeExecutorState ( estate ) ;
 return ( Expr * ) makeConst ( result_type , result_typmod , result_collation , resultTypLen , const_val , const_is_null , resultTypByVal ) ;
 }