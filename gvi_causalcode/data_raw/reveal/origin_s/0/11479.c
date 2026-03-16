static double scalarineqsel ( PlannerInfo * root , Oid operator , bool isgt , VariableStatData * vardata , Datum constval , Oid consttype ) {
 Form_pg_statistic stats ;
 FmgrInfo opproc ;
 double mcv_selec , hist_selec , sumcommon ;
 double selec ;
 if ( ! HeapTupleIsValid ( vardata -> statsTuple ) ) {
 return DEFAULT_INEQ_SEL ;
 }
 stats = ( Form_pg_statistic ) GETSTRUCT ( vardata -> statsTuple ) ;
 fmgr_info ( get_opcode ( operator ) , & opproc ) ;
 mcv_selec = mcv_selectivity ( vardata , & opproc , constval , true , & sumcommon ) ;
 hist_selec = ineq_histogram_selectivity ( root , vardata , & opproc , isgt , constval , consttype ) ;
 selec = 1.0 - stats -> stanullfrac - sumcommon ;
 if ( hist_selec >= 0.0 ) selec *= hist_selec ;
 else {
 selec *= 0.5 ;
 }
 selec += mcv_selec ;
 CLAMP_PROBABILITY ( selec ) ;
 return selec ;
 }