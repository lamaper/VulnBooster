bool is_pseudo_constant_clause ( Node * clause ) {
 if ( ! contain_var_clause ( clause ) && ! contain_volatile_functions ( clause ) ) return true ;
 return false ;
 }