static RelOptInfo * find_join_input_rel ( PlannerInfo * root , Relids relids ) {
 RelOptInfo * rel = NULL ;
 switch ( bms_membership ( relids ) ) {
 case BMS_EMPTY_SET : break ;
 case BMS_SINGLETON : rel = find_base_rel ( root , bms_singleton_member ( relids ) ) ;
 break ;
 case BMS_MULTIPLE : rel = find_join_rel ( root , relids ) ;
 break ;
 }
 if ( rel == NULL ) elog ( ERROR , "could not find RelOptInfo for given relids" ) ;
 return rel ;
 }