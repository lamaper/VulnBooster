static int casecmp ( const chr * x , const chr * y , size_t len ) {
 for ( ;
 len > 0 ;
 len -- , x ++ , y ++ ) {
 if ( ( * x != * y ) && ( pg_wc_tolower ( * x ) != pg_wc_tolower ( * y ) ) ) return 1 ;
 }
 return 0 ;
 }