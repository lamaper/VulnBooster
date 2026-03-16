static bool find_next_mcelem ( Datum * mcelem , int nmcelem , Datum value , int * index , FmgrInfo * cmpfunc ) {
 int l = * index , r = nmcelem - 1 , i , res ;
 while ( l <= r ) {
 i = ( l + r ) / 2 ;
 res = element_compare ( & mcelem [ i ] , & value , cmpfunc ) ;
 if ( res == 0 ) {
 * index = i ;
 return true ;
 }
 else if ( res < 0 ) l = i + 1 ;
 else r = i - 1 ;
 }
 * index = l ;
 return false ;
 }