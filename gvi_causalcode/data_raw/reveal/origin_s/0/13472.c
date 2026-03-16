static void addrsort ( char * * ap , int num ) {
 int i , j ;
 char * * p ;
 short aval [ MAX_NR_ADDRS ] ;
 int needsort = 0 ;
 p = ap ;
 if ( num > MAX_NR_ADDRS ) num = MAX_NR_ADDRS ;
 for ( i = 0 ;
 i < num ;
 i ++ , p ++ ) {
 for ( j = 0 ;
 ( unsigned ) j < _res . nsort ;
 j ++ ) if ( _res . sort_list [ j ] . addr . s_addr == ( ( ( struct in_addr * ) ( * p ) ) -> s_addr & _res . sort_list [ j ] . mask ) ) break ;
 aval [ i ] = j ;
 if ( needsort == 0 && i > 0 && j < aval [ i - 1 ] ) needsort = i ;
 }
 if ( ! needsort ) return ;
 while ( needsort ++ < num ) for ( j = needsort - 2 ;
 j >= 0 ;
 j -- ) if ( aval [ j ] > aval [ j + 1 ] ) {
 char * hp ;
 i = aval [ j ] ;
 aval [ j ] = aval [ j + 1 ] ;
 aval [ j + 1 ] = i ;
 hp = ap [ j ] ;
 ap [ j ] = ap [ j + 1 ] ;
 ap [ j + 1 ] = hp ;
 }
 else break ;
 }