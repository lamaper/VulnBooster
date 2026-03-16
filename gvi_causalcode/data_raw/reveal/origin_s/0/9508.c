static void freelacons ( struct subre * subs , int n ) {
 struct subre * sub ;
 int i ;
 assert ( n > 0 ) ;
 for ( sub = subs + 1 , i = n - 1 ;
 i > 0 ;
 sub ++ , i -- ) if ( ! NULLCNFA ( sub -> cnfa ) ) freecnfa ( & sub -> cnfa ) ;
 FREE ( subs ) ;
 }