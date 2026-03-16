static Selectivity prefix_selectivity ( PlannerInfo * root , VariableStatData * vardata , Oid vartype , Oid opfamily , Const * prefixcon ) {
 Selectivity prefixsel ;
 Oid cmpopr ;
 FmgrInfo opproc ;
 Const * greaterstrcon ;
 Selectivity eq_sel ;
 cmpopr = get_opfamily_member ( opfamily , vartype , vartype , BTGreaterEqualStrategyNumber ) ;
 if ( cmpopr == InvalidOid ) elog ( ERROR , "no >= operator for opfamily %u" , opfamily ) ;
 fmgr_info ( get_opcode ( cmpopr ) , & opproc ) ;
 prefixsel = ineq_histogram_selectivity ( root , vardata , & opproc , true , prefixcon -> constvalue , prefixcon -> consttype ) ;
 if ( prefixsel < 0.0 ) {
 return DEFAULT_MATCH_SEL ;
 }
 cmpopr = get_opfamily_member ( opfamily , vartype , vartype , BTLessStrategyNumber ) ;
 if ( cmpopr == InvalidOid ) elog ( ERROR , "no < operator for opfamily %u" , opfamily ) ;
 fmgr_info ( get_opcode ( cmpopr ) , & opproc ) ;
 greaterstrcon = make_greater_string ( prefixcon , & opproc , DEFAULT_COLLATION_OID ) ;
 if ( greaterstrcon ) {
 Selectivity topsel ;
 topsel = ineq_histogram_selectivity ( root , vardata , & opproc , false , greaterstrcon -> constvalue , greaterstrcon -> consttype ) ;
 Assert ( topsel >= 0.0 ) ;
 prefixsel = topsel + prefixsel - 1.0 ;
 }
 cmpopr = get_opfamily_member ( opfamily , vartype , vartype , BTEqualStrategyNumber ) ;
 if ( cmpopr == InvalidOid ) elog ( ERROR , "no = operator for opfamily %u" , opfamily ) ;
 eq_sel = var_eq_const ( vardata , cmpopr , prefixcon -> constvalue , false , true ) ;
 prefixsel = Max ( prefixsel , eq_sel ) ;
 return prefixsel ;
 }