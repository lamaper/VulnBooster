Node * get_rightop ( const Expr * clause ) {
 const OpExpr * expr = ( const OpExpr * ) clause ;
 if ( list_length ( expr -> args ) >= 2 ) return lsecond ( expr -> args ) ;
 else return NULL ;
 }