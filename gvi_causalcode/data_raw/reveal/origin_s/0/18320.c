static List * add_unique_group_var ( PlannerInfo * root , List * varinfos , Node * var , VariableStatData * vardata ) {
 GroupVarInfo * varinfo ;
 double ndistinct ;
 bool isdefault ;
 ListCell * lc ;
 ndistinct = get_variable_numdistinct ( vardata , & isdefault ) ;
 lc = list_head ( varinfos ) ;
 while ( lc ) {
 varinfo = ( GroupVarInfo * ) lfirst ( lc ) ;
 lc = lnext ( lc ) ;
 if ( equal ( var , varinfo -> var ) ) return varinfos ;
 if ( vardata -> rel != varinfo -> rel && exprs_known_equal ( root , var , varinfo -> var ) ) {
 if ( varinfo -> ndistinct <= ndistinct ) {
 return varinfos ;
 }
 else {
 varinfos = list_delete_ptr ( varinfos , varinfo ) ;
 }
 }
 }
 varinfo = ( GroupVarInfo * ) palloc ( sizeof ( GroupVarInfo ) ) ;
 varinfo -> var = var ;
 varinfo -> rel = vardata -> rel ;
 varinfo -> ndistinct = ndistinct ;
 varinfos = lappend ( varinfos , varinfo ) ;
 return varinfos ;
 }