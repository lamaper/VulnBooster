static guint call_list_length ( call_list * list ) {
 guint count = 0 ;
 for ( ;
 list ;
 list = list -> next ) {
 count ++ ;
 }
 return count ;
 }