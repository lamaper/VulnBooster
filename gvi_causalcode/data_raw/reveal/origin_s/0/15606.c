static bool contain_leaked_vars_walker ( Node * node , void * context ) {
 if ( node == NULL ) return false ;
 switch ( nodeTag ( node ) ) {
 case T_Var : case T_Const : case T_Param : case T_ArrayRef : case T_ArrayExpr : case T_FieldSelect : case T_FieldStore : case T_NamedArgExpr : case T_BoolExpr : case T_RelabelType : case T_CollateExpr : case T_CaseExpr : case T_CaseTestExpr : case T_RowExpr : case T_MinMaxExpr : case T_NullTest : case T_BooleanTest : case T_List : break ;
 case T_FuncExpr : case T_OpExpr : case T_DistinctExpr : case T_NullIfExpr : case T_ScalarArrayOpExpr : case T_CoerceViaIO : case T_ArrayCoerceExpr : if ( check_functions_in_node ( node , contain_leaked_vars_checker , context ) && contain_var_clause ( node ) ) return true ;
 break ;
 case T_RowCompareExpr : {
 RowCompareExpr * rcexpr = ( RowCompareExpr * ) node ;
 ListCell * opid ;
 ListCell * larg ;
 ListCell * rarg ;
 forthree ( opid , rcexpr -> opnos , larg , rcexpr -> largs , rarg , rcexpr -> rargs ) {
 Oid funcid = get_opcode ( lfirst_oid ( opid ) ) ;
 if ( ! get_func_leakproof ( funcid ) && ( contain_var_clause ( ( Node * ) lfirst ( larg ) ) || contain_var_clause ( ( Node * ) lfirst ( rarg ) ) ) ) return true ;
 }
 }
 break ;
 case T_CurrentOfExpr : return false ;
 default : return true ;
 }
 return expression_tree_walker ( node , contain_leaked_vars_walker , context ) ;
 }