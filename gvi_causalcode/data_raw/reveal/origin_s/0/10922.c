static int get_search_range ( const VP9_COMMON * cm ) {
 int sr = 0 ;
 const int dim = MIN ( cm -> width , cm -> height ) ;
 while ( ( dim << sr ) < MAX_FULL_PEL_VAL ) ++ sr ;
 return sr ;
 }