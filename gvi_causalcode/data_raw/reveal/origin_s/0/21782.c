static void decReverse ( Unit * ulo , Unit * uhi ) {
 Unit temp ;
 for ( ;
 ulo < uhi ;
 ulo ++ , uhi -- ) {
 temp = * ulo ;
 * ulo = * uhi ;
 * uhi = temp ;
 }
 return ;
 }