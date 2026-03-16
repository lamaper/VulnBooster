Datum scalarltsel ( PG_FUNCTION_ARGS ) {
 PlannerInfo * root = ( PlannerInfo * ) PG_GETARG_POINTER ( 0 ) ;
 Oid operator = PG_GETARG_OID ( 1 ) ;
 List * args = ( List * ) PG_GETARG_POINTER ( 2 ) ;
 int varRelid = PG_GETARG_INT32 ( 3 ) ;
 VariableStatData vardata ;
 Node * other ;
 bool varonleft ;
 Datum constval ;
 Oid consttype ;
 bool isgt ;
 double selec ;
 if ( ! get_restriction_variable ( root , args , varRelid , & vardata , & other , & varonleft ) ) PG_RETURN_FLOAT8 ( DEFAULT_INEQ_SEL ) ;
 if ( ! IsA ( other , Const ) ) {
 ReleaseVariableStats ( vardata ) ;
 PG_RETURN_FLOAT8 ( DEFAULT_INEQ_SEL ) ;
 }
 if ( ( ( Const * ) other ) -> constisnull ) {
 ReleaseVariableStats ( vardata ) ;
 PG_RETURN_FLOAT8 ( 0.0 ) ;
 }
 constval = ( ( Const * ) other ) -> constvalue ;
 consttype = ( ( Const * ) other ) -> consttype ;
 if ( varonleft ) {
 isgt = false ;
 }
 else {
 operator = get_commutator ( operator ) ;
 if ( ! operator ) {
 ReleaseVariableStats ( vardata ) ;
 PG_RETURN_FLOAT8 ( DEFAULT_INEQ_SEL ) ;
 }
 isgt = true ;
 }
 selec = scalarineqsel ( root , operator , isgt , & vardata , constval , consttype ) ;
 ReleaseVariableStats ( vardata ) ;
 PG_RETURN_FLOAT8 ( ( float8 ) selec ) ;
 }