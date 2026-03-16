Datum eqsel ( PG_FUNCTION_ARGS ) {
 PlannerInfo * root = ( PlannerInfo * ) PG_GETARG_POINTER ( 0 ) ;
 Oid operator = PG_GETARG_OID ( 1 ) ;
 List * args = ( List * ) PG_GETARG_POINTER ( 2 ) ;
 int varRelid = PG_GETARG_INT32 ( 3 ) ;
 VariableStatData vardata ;
 Node * other ;
 bool varonleft ;
 double selec ;
 if ( ! get_restriction_variable ( root , args , varRelid , & vardata , & other , & varonleft ) ) PG_RETURN_FLOAT8 ( DEFAULT_EQ_SEL ) ;
 if ( IsA ( other , Const ) ) selec = var_eq_const ( & vardata , operator , ( ( Const * ) other ) -> constvalue , ( ( Const * ) other ) -> constisnull , varonleft ) ;
 else selec = var_eq_non_const ( & vardata , operator , other , varonleft ) ;
 ReleaseVariableStats ( vardata ) ;
 PG_RETURN_FLOAT8 ( ( float8 ) selec ) ;
 }