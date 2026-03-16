static int newlacon ( struct vars * v , struct state * begin , struct state * end , int latype ) {
 int n ;
 struct subre * newlacons ;
 struct subre * sub ;
 if ( v -> nlacons == 0 ) {
 n = 1 ;
 newlacons = ( struct subre * ) MALLOC ( 2 * sizeof ( struct subre ) ) ;
 }
 else {
 n = v -> nlacons ;
 newlacons = ( struct subre * ) REALLOC ( v -> lacons , ( n + 1 ) * sizeof ( struct subre ) ) ;
 }
 if ( newlacons == NULL ) {
 ERR ( REG_ESPACE ) ;
 return 0 ;
 }
 v -> lacons = newlacons ;
 v -> nlacons = n + 1 ;
 sub = & v -> lacons [ n ] ;
 sub -> begin = begin ;
 sub -> end = end ;
 sub -> subno = latype ;
 ZAPCNFA ( sub -> cnfa ) ;
 return n ;
 }