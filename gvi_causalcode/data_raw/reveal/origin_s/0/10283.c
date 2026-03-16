static double patternsel ( PG_FUNCTION_ARGS , Pattern_Type ptype , bool negate ) {
 PlannerInfo * root = ( PlannerInfo * ) PG_GETARG_POINTER ( 0 ) ;
 Oid operator = PG_GETARG_OID ( 1 ) ;
 List * args = ( List * ) PG_GETARG_POINTER ( 2 ) ;
 int varRelid = PG_GETARG_INT32 ( 3 ) ;
 Oid collation = PG_GET_COLLATION ( ) ;
 VariableStatData vardata ;
 Node * other ;
 bool varonleft ;
 Datum constval ;
 Oid consttype ;
 Oid vartype ;
 Oid opfamily ;
 Pattern_Prefix_Status pstatus ;
 Const * patt ;
 Const * prefix = NULL ;
 Selectivity rest_selec = 0 ;
 double result ;
 if ( negate ) {
 operator = get_negator ( operator ) ;
 if ( ! OidIsValid ( operator ) ) elog ( ERROR , "patternsel called for operator without a negator" ) ;
 result = 1.0 - DEFAULT_MATCH_SEL ;
 }
 else {
 result = DEFAULT_MATCH_SEL ;
 }
 if ( ! get_restriction_variable ( root , args , varRelid , & vardata , & other , & varonleft ) ) return result ;
 if ( ! varonleft || ! IsA ( other , Const ) ) {
 ReleaseVariableStats ( vardata ) ;
 return result ;
 }
 if ( ( ( Const * ) other ) -> constisnull ) {
 ReleaseVariableStats ( vardata ) ;
 return 0.0 ;
 }
 constval = ( ( Const * ) other ) -> constvalue ;
 consttype = ( ( Const * ) other ) -> consttype ;
 if ( consttype != TEXTOID && consttype != BYTEAOID ) {
 ReleaseVariableStats ( vardata ) ;
 return result ;
 }
 vartype = vardata . vartype ;
 switch ( vartype ) {
 case TEXTOID : opfamily = TEXT_BTREE_FAM_OID ;
 break ;
 case BPCHAROID : opfamily = BPCHAR_BTREE_FAM_OID ;
 break ;
 case NAMEOID : opfamily = NAME_BTREE_FAM_OID ;
 break ;
 case BYTEAOID : opfamily = BYTEA_BTREE_FAM_OID ;
 break ;
 default : ReleaseVariableStats ( vardata ) ;
 return result ;
 }
 patt = ( Const * ) other ;
 pstatus = pattern_fixed_prefix ( patt , ptype , collation , & prefix , & rest_selec ) ;
 if ( prefix && prefix -> consttype != vartype ) {
 char * prefixstr ;
 switch ( prefix -> consttype ) {
 case TEXTOID : prefixstr = TextDatumGetCString ( prefix -> constvalue ) ;
 break ;
 case BYTEAOID : prefixstr = DatumGetCString ( DirectFunctionCall1 ( byteaout , prefix -> constvalue ) ) ;
 break ;
 default : elog ( ERROR , "unrecognized consttype: %u" , prefix -> consttype ) ;
 ReleaseVariableStats ( vardata ) ;
 return result ;
 }
 prefix = string_to_const ( prefixstr , vartype ) ;
 pfree ( prefixstr ) ;
 }
 if ( pstatus == Pattern_Prefix_Exact ) {
 Oid eqopr = get_opfamily_member ( opfamily , vartype , vartype , BTEqualStrategyNumber ) ;
 if ( eqopr == InvalidOid ) elog ( ERROR , "no = operator for opfamily %u" , opfamily ) ;
 result = var_eq_const ( & vardata , eqopr , prefix -> constvalue , false , true ) ;
 }
 else {
 Selectivity selec ;
 int hist_size ;
 FmgrInfo opproc ;
 double nullfrac , mcv_selec , sumcommon ;
 fmgr_info ( get_opcode ( operator ) , & opproc ) ;
 selec = histogram_selectivity ( & vardata , & opproc , constval , true , 10 , 1 , & hist_size ) ;
 if ( hist_size < 100 ) {
 Selectivity heursel ;
 Selectivity prefixsel ;
 if ( pstatus == Pattern_Prefix_Partial ) prefixsel = prefix_selectivity ( root , & vardata , vartype , opfamily , prefix ) ;
 else prefixsel = 1.0 ;
 heursel = prefixsel * rest_selec ;
 if ( selec < 0 ) selec = heursel ;
 else {
 double hist_weight = hist_size / 100.0 ;
 selec = selec * hist_weight + heursel * ( 1.0 - hist_weight ) ;
 }
 }
 if ( selec < 0.0001 ) selec = 0.0001 ;
 else if ( selec > 0.9999 ) selec = 0.9999 ;
 mcv_selec = mcv_selectivity ( & vardata , & opproc , constval , true , & sumcommon ) ;
 if ( HeapTupleIsValid ( vardata . statsTuple ) ) nullfrac = ( ( Form_pg_statistic ) GETSTRUCT ( vardata . statsTuple ) ) -> stanullfrac ;
 else nullfrac = 0.0 ;
 selec *= 1.0 - nullfrac - sumcommon ;
 selec += mcv_selec ;
 CLAMP_PROBABILITY ( selec ) ;
 result = selec ;
 }
 if ( prefix ) {
 pfree ( DatumGetPointer ( prefix -> constvalue ) ) ;
 pfree ( prefix ) ;
 }
 ReleaseVariableStats ( vardata ) ;
 return negate ? ( 1.0 - result ) : result ;
 }