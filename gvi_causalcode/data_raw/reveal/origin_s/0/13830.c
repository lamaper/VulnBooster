static void collectgarbage ( struct garbage * tofrees , struct pskeydict * to ) {
 struct garbage * into ;
 into = tofrees ;
 if ( tofrees -> cnt >= GARBAGE_MAX && tofrees -> next != NULL ) into = tofrees -> next ;
 if ( into -> cnt >= GARBAGE_MAX ) {
 into = chunkalloc ( sizeof ( struct garbage ) ) ;
 into -> next = tofrees -> next ;
 tofrees -> next = into ;
 }
 into -> cnts [ into -> cnt ] = to -> cnt ;
 into -> entries [ into -> cnt ++ ] = to -> entries ;
 }