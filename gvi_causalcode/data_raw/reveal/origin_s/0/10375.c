static int cmp ( const chr * x , const chr * y , size_t len ) {
 return memcmp ( VS ( x ) , VS ( y ) , len * sizeof ( chr ) ) ;
 }