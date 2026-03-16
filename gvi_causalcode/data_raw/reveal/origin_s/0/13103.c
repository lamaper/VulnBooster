Selectivity estimate_hash_bucketsize ( PlannerInfo * root , Node * hashkey , double nbuckets ) {
 VariableStatData vardata ;
 double estfract , ndistinct , stanullfrac , mcvfreq , avgfreq ;
 bool isdefault ;
 float4 * numbers ;
 int nnumbers ;
 examine_variable ( root , hashkey , 0 , & vardata ) ;
 ndistinct = get_variable_numdistinct ( & vardata , & isdefault ) ;
 if ( isdefault ) {
 ReleaseVariableStats ( vardata ) ;
 return ( Selectivity ) 0.1 ;
 }
 if ( HeapTupleIsValid ( vardata . statsTuple ) ) {
 Form_pg_statistic stats ;
 stats = ( Form_pg_statistic ) GETSTRUCT ( vardata . statsTuple ) ;
 stanullfrac = stats -> stanullfrac ;
 }
 else stanullfrac = 0.0 ;
 avgfreq = ( 1.0 - stanullfrac ) / ndistinct ;
 if ( vardata . rel && vardata . rel -> tuples > 0 ) {
 ndistinct *= vardata . rel -> rows / vardata . rel -> tuples ;
 ndistinct = clamp_row_est ( ndistinct ) ;
 }
 if ( ndistinct > nbuckets ) estfract = 1.0 / nbuckets ;
 else estfract = 1.0 / ndistinct ;
 mcvfreq = 0.0 ;
 if ( HeapTupleIsValid ( vardata . statsTuple ) ) {
 if ( get_attstatsslot ( vardata . statsTuple , vardata . atttype , vardata . atttypmod , STATISTIC_KIND_MCV , InvalidOid , NULL , NULL , NULL , & numbers , & nnumbers ) ) {
 if ( nnumbers > 0 ) mcvfreq = numbers [ 0 ] ;
 free_attstatsslot ( vardata . atttype , NULL , 0 , numbers , nnumbers ) ;
 }
 }
 if ( avgfreq > 0.0 && mcvfreq > avgfreq ) estfract *= mcvfreq / avgfreq ;
 if ( estfract < 1.0e-6 ) estfract = 1.0e-6 ;
 else if ( estfract > 1.0 ) estfract = 1.0 ;
 ReleaseVariableStats ( vardata ) ;
 return ( Selectivity ) estfract ;
 }