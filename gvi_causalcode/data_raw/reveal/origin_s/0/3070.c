Relids find_nonnullable_rels ( Node * clause ) {
 return find_nonnullable_rels_walker ( clause , true ) ;
 }