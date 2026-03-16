WindowFuncLists * find_window_functions ( Node * clause , Index maxWinRef ) {
 WindowFuncLists * lists = palloc ( sizeof ( WindowFuncLists ) ) ;
 lists -> numWindowFuncs = 0 ;
 lists -> maxWinRef = maxWinRef ;
 lists -> windowFuncs = ( List * * ) palloc0 ( ( maxWinRef + 1 ) * sizeof ( List * ) ) ;
 ( void ) find_window_functions_walker ( clause , lists ) ;
 return lists ;
 }