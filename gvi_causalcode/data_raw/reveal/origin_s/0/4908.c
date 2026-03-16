static bool find_window_functions_walker ( Node * node , WindowFuncLists * lists ) {
 if ( node == NULL ) return false ;
 if ( IsA ( node , WindowFunc ) ) {
 WindowFunc * wfunc = ( WindowFunc * ) node ;
 if ( wfunc -> winref > lists -> maxWinRef ) elog ( ERROR , "WindowFunc contains out-of-range winref %u" , wfunc -> winref ) ;
 if ( ! list_member ( lists -> windowFuncs [ wfunc -> winref ] , wfunc ) ) {
 lists -> windowFuncs [ wfunc -> winref ] = lappend ( lists -> windowFuncs [ wfunc -> winref ] , wfunc ) ;
 lists -> numWindowFuncs ++ ;
 }
 return false ;
 }
 Assert ( ! IsA ( node , SubLink ) ) ;
 return expression_tree_walker ( node , find_window_functions_walker , ( void * ) lists ) ;
 }