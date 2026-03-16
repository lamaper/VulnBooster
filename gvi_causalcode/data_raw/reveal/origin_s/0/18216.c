static void lexnest ( struct vars * v , const chr * beginp , const chr * endp ) {
 assert ( v -> savenow == NULL ) ;
 v -> savenow = v -> now ;
 v -> savestop = v -> stop ;
 v -> now = beginp ;
 v -> stop = endp ;
 }