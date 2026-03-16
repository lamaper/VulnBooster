int vp9_init_search_range ( int size ) {
 int sr = 0 ;
 size = MAX ( 16 , size ) ;
 while ( ( size << sr ) < MAX_FULL_PEL_VAL ) sr ++ ;
 sr = MIN ( sr , MAX_MVSEARCH_STEPS - 2 ) ;
 return sr ;
 }