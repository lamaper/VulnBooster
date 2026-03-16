void get_join_variables ( PlannerInfo * root , List * args , SpecialJoinInfo * sjinfo , VariableStatData * vardata1 , VariableStatData * vardata2 , bool * join_is_reversed ) {
 Node * left , * right ;
 if ( list_length ( args ) != 2 ) elog ( ERROR , "join operator should take two arguments" ) ;
 left = ( Node * ) linitial ( args ) ;
 right = ( Node * ) lsecond ( args ) ;
 examine_variable ( root , left , 0 , vardata1 ) ;
 examine_variable ( root , right , 0 , vardata2 ) ;
 if ( vardata1 -> rel && bms_is_subset ( vardata1 -> rel -> relids , sjinfo -> syn_righthand ) ) * join_is_reversed = true ;
 else if ( vardata2 -> rel && bms_is_subset ( vardata2 -> rel -> relids , sjinfo -> syn_lefthand ) ) * join_is_reversed = true ;
 else * join_is_reversed = false ;
 }