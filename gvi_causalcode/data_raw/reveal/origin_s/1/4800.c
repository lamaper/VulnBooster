static void fd_free_list ( struct FrameData * list ) {
 struct FrameData * p = list ;
 while ( p ) {
 list = list -> next ;
 fd_free ( p ) ;
 p = list ;
 }
 }