static Selectivity mcelem_array_contained_selec ( Datum * mcelem , int nmcelem , float4 * numbers , int nnumbers , Datum * array_data , int nitems , float4 * hist , int nhist , Oid operator , FmgrInfo * cmpfunc ) {
 int mcelem_index , i , unique_nitems = 0 ;
 float selec , minfreq , nullelem_freq ;
 float * dist , * mcelem_dist , * hist_part ;
 float avg_count , mult , rest ;
 float * elem_selec ;
 if ( numbers == NULL || nnumbers != nmcelem + 3 ) return DEFAULT_CONTAIN_SEL ;
 if ( hist == NULL || nhist < 3 ) return DEFAULT_CONTAIN_SEL ;
 minfreq = numbers [ nmcelem ] ;
 nullelem_freq = numbers [ nmcelem + 2 ] ;
 avg_count = hist [ nhist - 1 ] ;
 rest = avg_count ;
 mult = 1.0f ;
 elem_selec = ( float * ) palloc ( sizeof ( float ) * nitems ) ;
 mcelem_index = 0 ;
 for ( i = 0 ;
 i < nitems ;
 i ++ ) {
 bool match = false ;
 if ( i > 0 && element_compare ( & array_data [ i - 1 ] , & array_data [ i ] , cmpfunc ) == 0 ) continue ;
 while ( mcelem_index < nmcelem ) {
 int cmp = element_compare ( & mcelem [ mcelem_index ] , & array_data [ i ] , cmpfunc ) ;
 if ( cmp < 0 ) {
 mult *= ( 1.0f - numbers [ mcelem_index ] ) ;
 rest -= numbers [ mcelem_index ] ;
 mcelem_index ++ ;
 }
 else {
 if ( cmp == 0 ) match = true ;
 break ;
 }
 }
 if ( match ) {
 elem_selec [ unique_nitems ] = numbers [ mcelem_index ] ;
 rest -= numbers [ mcelem_index ] ;
 mcelem_index ++ ;
 }
 else {
 elem_selec [ unique_nitems ] = Min ( DEFAULT_CONTAIN_SEL , minfreq / 2 ) ;
 }
 unique_nitems ++ ;
 }
 while ( mcelem_index < nmcelem ) {
 mult *= ( 1.0f - numbers [ mcelem_index ] ) ;
 rest -= numbers [ mcelem_index ] ;
 mcelem_index ++ ;
 }
 mult *= exp ( - rest ) ;

 double b = ( double ) nmcelem ;
 int n ;
 n = ( int ) ( ( sqrt ( b * b + 4 * EFFORT * b ) - b ) / 2 ) ;
 qsort ( elem_selec , unique_nitems , sizeof ( float ) , float_compare_desc ) ;
 unique_nitems = n ;
 }
 dist = calc_distr ( elem_selec , unique_nitems , unique_nitems , 0.0f ) ;
 mcelem_dist = calc_distr ( numbers , nmcelem , unique_nitems , rest ) ;
 hist_part = calc_hist ( hist , nhist - 1 , unique_nitems ) ;
 selec = 0.0f ;
 for ( i = 0 ;
 i <= unique_nitems ;
 i ++ ) {
 if ( mcelem_dist [ i ] > 0 ) selec += hist_part [ i ] * mult * dist [ i ] / mcelem_dist [ i ] ;
 }
 pfree ( dist ) ;
 pfree ( mcelem_dist ) ;
 pfree ( hist_part ) ;
 pfree ( elem_selec ) ;
 selec *= ( 1.0f - nullelem_freq ) ;
 CLAMP_PROBABILITY ( selec ) ;
 return selec ;
 }