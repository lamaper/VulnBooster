static List * simplify_or_arguments ( List * args , eval_const_expressions_context * context , bool * haveNull , bool * forceTrue ) {
 List * newargs = NIL ;
 List * unprocessed_args ;
 unprocessed_args = list_copy ( args ) ;
 while ( unprocessed_args ) {
 Node * arg = ( Node * ) linitial ( unprocessed_args ) ;
 unprocessed_args = list_delete_first ( unprocessed_args ) ;
 if ( or_clause ( arg ) ) {
 List * subargs = list_copy ( ( ( BoolExpr * ) arg ) -> args ) ;
 if ( ! unprocessed_args ) unprocessed_args = subargs ;
 else {
 List * oldhdr = unprocessed_args ;
 unprocessed_args = list_concat ( subargs , unprocessed_args ) ;
 pfree ( oldhdr ) ;
 }
 continue ;
 }
 arg = eval_const_expressions_mutator ( arg , context ) ;
 if ( or_clause ( arg ) ) {
 List * subargs = list_copy ( ( ( BoolExpr * ) arg ) -> args ) ;
 unprocessed_args = list_concat ( subargs , unprocessed_args ) ;
 continue ;
 }
 if ( IsA ( arg , Const ) ) {
 Const * const_input = ( Const * ) arg ;
 if ( const_input -> constisnull ) * haveNull = true ;
 else if ( DatumGetBool ( const_input -> constvalue ) ) {
 * forceTrue = true ;
 return NIL ;
 }
 continue ;
 }
 newargs = lappend ( newargs , arg ) ;
 }
 return newargs ;
 }