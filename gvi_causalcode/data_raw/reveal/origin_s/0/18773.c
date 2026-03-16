bool is_pseudo_constant_clause_relids ( Node * clause , Relids relids ) {
 if ( bms_is_empty ( relids ) && ! contain_volatile_functions ( clause ) ) return true ;
 return false ;
 }