static int huff_cmp ( const void * va , const void * vb ) {
 const Node * a = va , * b = vb ;
 return ( a -> count - b -> count ) * 256 + a -> sym - b -> sym ;
 }