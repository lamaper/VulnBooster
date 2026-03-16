static void moresubs ( struct vars * v , int wanted ) {
 struct subre * * p ;
 size_t n ;
 assert ( wanted > 0 && ( size_t ) wanted >= v -> nsubs ) ;
 n = ( size_t ) wanted * 3 / 2 + 1 ;
 if ( v -> subs == v -> sub10 ) {
 p = ( struct subre * * ) MALLOC ( n * sizeof ( struct subre * ) ) ;
 if ( p != NULL ) memcpy ( VS ( p ) , VS ( v -> subs ) , v -> nsubs * sizeof ( struct subre * ) ) ;
 }
 else p = ( struct subre * * ) REALLOC ( v -> subs , n * sizeof ( struct subre * ) ) ;
 if ( p == NULL ) {
 ERR ( REG_ESPACE ) ;
 return ;
 }
 v -> subs = p ;
 for ( p = & v -> subs [ v -> nsubs ] ;
 v -> nsubs < n ;
 p ++ , v -> nsubs ++ ) * p = NULL ;
 assert ( v -> nsubs == n ) ;
 assert ( ( size_t ) wanted < v -> nsubs ) ;
 }