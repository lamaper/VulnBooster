Datum arraycontsel ( PG_FUNCTION_ARGS ) {
 PlannerInfo * root = ( PlannerInfo * ) PG_GETARG_POINTER ( 0 ) ;
 Oid operator = PG_GETARG_OID ( 1 ) ;
 List * args = ( List * ) PG_GETARG_POINTER ( 2 ) ;
 int varRelid = PG_GETARG_INT32 ( 3 ) ;
 VariableStatData vardata ;
 Node * other ;
 bool varonleft ;
 Selectivity selec ;
 Oid element_typeid ;
 if ( ! get_restriction_variable ( root , args , varRelid , & vardata , & other , & varonleft ) ) PG_RETURN_FLOAT8 ( DEFAULT_SEL ( operator ) ) ;
 if ( ! IsA ( other , Const ) ) {
 ReleaseVariableStats ( vardata ) ;
 PG_RETURN_FLOAT8 ( DEFAULT_SEL ( operator ) ) ;
 }
 if ( ( ( Const * ) other ) -> constisnull ) {
 ReleaseVariableStats ( vardata ) ;
 PG_RETURN_FLOAT8 ( 0.0 ) ;
 }
 if ( ! varonleft ) {
 if ( operator == OID_ARRAY_CONTAINS_OP ) operator = OID_ARRAY_CONTAINED_OP ;
 else if ( operator == OID_ARRAY_CONTAINED_OP ) operator = OID_ARRAY_CONTAINS_OP ;
 }
 element_typeid = get_base_element_type ( ( ( Const * ) other ) -> consttype ) ;
 if ( element_typeid != InvalidOid && element_typeid == get_base_element_type ( vardata . vartype ) ) {
 selec = calc_arraycontsel ( & vardata , ( ( Const * ) other ) -> constvalue , element_typeid , operator ) ;
 }
 else {
 selec = DEFAULT_SEL ( operator ) ;
 }
 ReleaseVariableStats ( vardata ) ;
 CLAMP_PROBABILITY ( selec ) ;
 PG_RETURN_FLOAT8 ( ( float8 ) selec ) ;
 }