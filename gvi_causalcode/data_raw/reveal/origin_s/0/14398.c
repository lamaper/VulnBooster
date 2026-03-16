Datum eqjoinsel ( PG_FUNCTION_ARGS ) {
 PlannerInfo * root = ( PlannerInfo * ) PG_GETARG_POINTER ( 0 ) ;
 Oid operator = PG_GETARG_OID ( 1 ) ;
 List * args = ( List * ) PG_GETARG_POINTER ( 2 ) ;


 double selec ;
 VariableStatData vardata1 ;
 VariableStatData vardata2 ;
 bool join_is_reversed ;
 RelOptInfo * inner_rel ;
 get_join_variables ( root , args , sjinfo , & vardata1 , & vardata2 , & join_is_reversed ) ;
 switch ( sjinfo -> jointype ) {
 case JOIN_INNER : case JOIN_LEFT : case JOIN_FULL : selec = eqjoinsel_inner ( operator , & vardata1 , & vardata2 ) ;
 break ;
 case JOIN_SEMI : case JOIN_ANTI : inner_rel = find_join_input_rel ( root , sjinfo -> min_righthand ) ;
 if ( ! join_is_reversed ) selec = eqjoinsel_semi ( operator , & vardata1 , & vardata2 , inner_rel ) ;
 else selec = eqjoinsel_semi ( get_commutator ( operator ) , & vardata2 , & vardata1 , inner_rel ) ;
 break ;
 default : elog ( ERROR , "unrecognized join type: %d" , ( int ) sjinfo -> jointype ) ;
 selec = 0 ;
 break ;
 }
 ReleaseVariableStats ( vardata1 ) ;
 ReleaseVariableStats ( vardata2 ) ;
 CLAMP_PROBABILITY ( selec ) ;
 PG_RETURN_FLOAT8 ( ( float8 ) selec ) ;
 }