void mergejoinscansel ( PlannerInfo * root , Node * clause , Oid opfamily , int strategy , bool nulls_first , Selectivity * leftstart , Selectivity * leftend , Selectivity * rightstart , Selectivity * rightend ) {
 Node * left , * right ;
 VariableStatData leftvar , rightvar ;
 int op_strategy ;
 Oid op_lefttype ;
 Oid op_righttype ;
 Oid opno , lsortop , rsortop , lstatop , rstatop , ltop , leop , revltop , revleop ;
 bool isgt ;
 Datum leftmin , leftmax , rightmin , rightmax ;
 double selec ;
 * leftstart = * rightstart = 0.0 ;
 * leftend = * rightend = 1.0 ;
 if ( ! is_opclause ( clause ) ) return ;
 opno = ( ( OpExpr * ) clause ) -> opno ;
 left = get_leftop ( ( Expr * ) clause ) ;
 right = get_rightop ( ( Expr * ) clause ) ;
 if ( ! right ) return ;
 examine_variable ( root , left , 0 , & leftvar ) ;
 examine_variable ( root , right , 0 , & rightvar ) ;
 get_op_opfamily_properties ( opno , opfamily , false , & op_strategy , & op_lefttype , & op_righttype ) ;
 Assert ( op_strategy == BTEqualStrategyNumber ) ;
 switch ( strategy ) {
 case BTLessStrategyNumber : isgt = false ;
 if ( op_lefttype == op_righttype ) {
 ltop = get_opfamily_member ( opfamily , op_lefttype , op_righttype , BTLessStrategyNumber ) ;
 leop = get_opfamily_member ( opfamily , op_lefttype , op_righttype , BTLessEqualStrategyNumber ) ;
 lsortop = ltop ;
 rsortop = ltop ;
 lstatop = lsortop ;
 rstatop = rsortop ;
 revltop = ltop ;
 revleop = leop ;
 }
 else {
 ltop = get_opfamily_member ( opfamily , op_lefttype , op_righttype , BTLessStrategyNumber ) ;
 leop = get_opfamily_member ( opfamily , op_lefttype , op_righttype , BTLessEqualStrategyNumber ) ;
 lsortop = get_opfamily_member ( opfamily , op_lefttype , op_lefttype , BTLessStrategyNumber ) ;
 rsortop = get_opfamily_member ( opfamily , op_righttype , op_righttype , BTLessStrategyNumber ) ;
 lstatop = lsortop ;
 rstatop = rsortop ;
 revltop = get_opfamily_member ( opfamily , op_righttype , op_lefttype , BTLessStrategyNumber ) ;
 revleop = get_opfamily_member ( opfamily , op_righttype , op_lefttype , BTLessEqualStrategyNumber ) ;
 }
 break ;
 case BTGreaterStrategyNumber : isgt = true ;
 if ( op_lefttype == op_righttype ) {
 ltop = get_opfamily_member ( opfamily , op_lefttype , op_righttype , BTGreaterStrategyNumber ) ;
 leop = get_opfamily_member ( opfamily , op_lefttype , op_righttype , BTGreaterEqualStrategyNumber ) ;
 lsortop = ltop ;
 rsortop = ltop ;
 lstatop = get_opfamily_member ( opfamily , op_lefttype , op_lefttype , BTLessStrategyNumber ) ;
 rstatop = lstatop ;
 revltop = ltop ;
 revleop = leop ;
 }
 else {
 ltop = get_opfamily_member ( opfamily , op_lefttype , op_righttype , BTGreaterStrategyNumber ) ;
 leop = get_opfamily_member ( opfamily , op_lefttype , op_righttype , BTGreaterEqualStrategyNumber ) ;
 lsortop = get_opfamily_member ( opfamily , op_lefttype , op_lefttype , BTGreaterStrategyNumber ) ;
 rsortop = get_opfamily_member ( opfamily , op_righttype , op_righttype , BTGreaterStrategyNumber ) ;
 lstatop = get_opfamily_member ( opfamily , op_lefttype , op_lefttype , BTLessStrategyNumber ) ;
 rstatop = get_opfamily_member ( opfamily , op_righttype , op_righttype , BTLessStrategyNumber ) ;
 revltop = get_opfamily_member ( opfamily , op_righttype , op_lefttype , BTGreaterStrategyNumber ) ;
 revleop = get_opfamily_member ( opfamily , op_righttype , op_lefttype , BTGreaterEqualStrategyNumber ) ;
 }
 break ;
 default : goto fail ;
 }
 if ( ! OidIsValid ( lsortop ) || ! OidIsValid ( rsortop ) || ! OidIsValid ( lstatop ) || ! OidIsValid ( rstatop ) || ! OidIsValid ( ltop ) || ! OidIsValid ( leop ) || ! OidIsValid ( revltop ) || ! OidIsValid ( revleop ) ) goto fail ;
 if ( ! isgt ) {
 if ( ! get_variable_range ( root , & leftvar , lstatop , & leftmin , & leftmax ) ) goto fail ;
 if ( ! get_variable_range ( root , & rightvar , rstatop , & rightmin , & rightmax ) ) goto fail ;
 }
 else {
 if ( ! get_variable_range ( root , & leftvar , lstatop , & leftmax , & leftmin ) ) goto fail ;
 if ( ! get_variable_range ( root , & rightvar , rstatop , & rightmax , & rightmin ) ) goto fail ;
 }
 selec = scalarineqsel ( root , leop , isgt , & leftvar , rightmax , op_righttype ) ;
 if ( selec != DEFAULT_INEQ_SEL ) * leftend = selec ;
 selec = scalarineqsel ( root , revleop , isgt , & rightvar , leftmax , op_lefttype ) ;
 if ( selec != DEFAULT_INEQ_SEL ) * rightend = selec ;
 if ( * leftend > * rightend ) * leftend = 1.0 ;
 else if ( * leftend < * rightend ) * rightend = 1.0 ;
 else * leftend = * rightend = 1.0 ;
 selec = scalarineqsel ( root , ltop , isgt , & leftvar , rightmin , op_righttype ) ;
 if ( selec != DEFAULT_INEQ_SEL ) * leftstart = selec ;
 selec = scalarineqsel ( root , revltop , isgt , & rightvar , leftmin , op_lefttype ) ;
 if ( selec != DEFAULT_INEQ_SEL ) * rightstart = selec ;
 if ( * leftstart < * rightstart ) * leftstart = 0.0 ;
 else if ( * leftstart > * rightstart ) * rightstart = 0.0 ;
 else * leftstart = * rightstart = 0.0 ;
 if ( nulls_first ) {
 Form_pg_statistic stats ;
 if ( HeapTupleIsValid ( leftvar . statsTuple ) ) {
 stats = ( Form_pg_statistic ) GETSTRUCT ( leftvar . statsTuple ) ;
 * leftstart += stats -> stanullfrac ;
 CLAMP_PROBABILITY ( * leftstart ) ;
 * leftend += stats -> stanullfrac ;
 CLAMP_PROBABILITY ( * leftend ) ;
 }
 if ( HeapTupleIsValid ( rightvar . statsTuple ) ) {
 stats = ( Form_pg_statistic ) GETSTRUCT ( rightvar . statsTuple ) ;
 * rightstart += stats -> stanullfrac ;
 CLAMP_PROBABILITY ( * rightstart ) ;
 * rightend += stats -> stanullfrac ;
 CLAMP_PROBABILITY ( * rightend ) ;
 }
 }
 if ( * leftstart >= * leftend ) {
 * leftstart = 0.0 ;
 * leftend = 1.0 ;
 }
 if ( * rightstart >= * rightend ) {
 * rightstart = 0.0 ;
 * rightend = 1.0 ;
 }
 fail : ReleaseVariableStats ( leftvar ) ;
 ReleaseVariableStats ( rightvar ) ;
 }