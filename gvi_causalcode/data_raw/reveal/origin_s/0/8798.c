static double var_eq_non_const ( VariableStatData * vardata , Oid operator , Node * other , bool varonleft ) {
 double selec ;
 bool isdefault ;
 if ( vardata -> isunique && vardata -> rel && vardata -> rel -> tuples >= 1.0 ) return 1.0 / vardata -> rel -> tuples ;
 if ( HeapTupleIsValid ( vardata -> statsTuple ) ) {
 Form_pg_statistic stats ;
 double ndistinct ;
 float4 * numbers ;
 int nnumbers ;
 stats = ( Form_pg_statistic ) GETSTRUCT ( vardata -> statsTuple ) ;
 selec = 1.0 - stats -> stanullfrac ;
 ndistinct = get_variable_numdistinct ( vardata , & isdefault ) ;
 if ( ndistinct > 1 ) selec /= ndistinct ;
 if ( get_attstatsslot ( vardata -> statsTuple , vardata -> atttype , vardata -> atttypmod , STATISTIC_KIND_MCV , InvalidOid , NULL , NULL , NULL , & numbers , & nnumbers ) ) {
 if ( nnumbers > 0 && selec > numbers [ 0 ] ) selec = numbers [ 0 ] ;
 free_attstatsslot ( vardata -> atttype , NULL , 0 , numbers , nnumbers ) ;
 }
 }
 else {
 selec = 1.0 / get_variable_numdistinct ( vardata , & isdefault ) ;
 }
 CLAMP_PROBABILITY ( selec ) ;
 return selec ;
 }