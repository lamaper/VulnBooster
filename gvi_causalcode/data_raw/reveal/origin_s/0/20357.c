static void hashglyphadd ( SplineChar * sc , UHash * uhash , NHash * nhash ) {
 int hash ;
 struct splinecharlist * test ;
 struct altuni * alt ;
 if ( sc -> unicodeenc == - 1 && sc -> altuni == NULL ) {
 hash = hashname ( sc -> name ) ;
 test = chunkalloc ( sizeof ( struct splinecharlist ) ) ;
 test -> sc = sc ;
 test -> next = ( * nhash ) [ hash ] ;
 ( * nhash ) [ hash ] = test ;
 }
 else if ( sc -> unicodeenc != - 1 ) {
 hash = sc -> unicodeenc & 0xffff ;
 test = chunkalloc ( sizeof ( struct splinecharlist ) ) ;
 test -> sc = sc ;
 test -> next = ( * uhash ) [ hash ] ;
 ( * uhash ) [ hash ] = test ;
 }
 for ( alt = sc -> altuni ;
 alt != NULL ;
 alt = alt -> next ) {
 hash = alt -> unienc & 0xffff ;
 test = chunkalloc ( sizeof ( struct splinecharlist ) ) ;
 test -> sc = sc ;
 test -> next = ( * uhash ) [ hash ] ;
 ( * uhash ) [ hash ] = test ;
 }
 }