double get_variable_numdistinct ( VariableStatData * vardata , bool * isdefault ) {
 double stadistinct ;
 double stanullfrac = 0.0 ;
 double ntuples ;
 * isdefault = false ;
 if ( HeapTupleIsValid ( vardata -> statsTuple ) ) {
 Form_pg_statistic stats ;
 stats = ( Form_pg_statistic ) GETSTRUCT ( vardata -> statsTuple ) ;
 stadistinct = stats -> stadistinct ;
 stanullfrac = stats -> stanullfrac ;
 }
 else if ( vardata -> vartype == BOOLOID ) {
 stadistinct = 2.0 ;
 }
 else {
 if ( vardata -> var && IsA ( vardata -> var , Var ) ) {
 switch ( ( ( Var * ) vardata -> var ) -> varattno ) {
 case ObjectIdAttributeNumber : case SelfItemPointerAttributeNumber : stadistinct = - 1.0 ;
 break ;
 case TableOidAttributeNumber : stadistinct = 1.0 ;
 break ;
 default : stadistinct = 0.0 ;
 break ;
 }
 }
 else stadistinct = 0.0 ;
 }
 if ( vardata -> isunique ) stadistinct = - 1.0 * ( 1.0 - stanullfrac ) ;
 if ( stadistinct > 0.0 ) return clamp_row_est ( stadistinct ) ;
 if ( vardata -> rel == NULL ) {
 * isdefault = true ;
 return DEFAULT_NUM_DISTINCT ;
 }
 ntuples = vardata -> rel -> tuples ;
 if ( ntuples <= 0.0 ) {
 * isdefault = true ;
 return DEFAULT_NUM_DISTINCT ;
 }
 if ( stadistinct < 0.0 ) return clamp_row_est ( - stadistinct * ntuples ) ;
 if ( ntuples < DEFAULT_NUM_DISTINCT ) return clamp_row_est ( ntuples ) ;
 * isdefault = true ;
 return DEFAULT_NUM_DISTINCT ;
 }