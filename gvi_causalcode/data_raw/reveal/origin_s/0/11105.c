static int32_t idCmp ( const char * id1 , const char * id2 ) {
 int32_t diffIdx = 0 ;
 while ( * id1 == * id2 && * id1 != 0 ) {
 diffIdx ++ ;
 id1 ++ ;
 id2 ++ ;
 }
 return diffIdx ;
 }