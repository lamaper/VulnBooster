static SplineChar * hashglyphfound ( SplineChar * sc , UHash * uhash , NHash * nhash , int layer ) {
 int hash ;
 struct splinecharlist * test ;
 struct altuni * alt ;
 if ( sc -> unicodeenc == - 1 && sc -> altuni == NULL ) {
 hash = hashname ( sc -> name ) ;
 for ( test = ( * nhash ) [ hash ] ;
 test != NULL ;
 test = test -> next ) if ( strcmp ( test -> sc -> name , sc -> name ) == 0 && glyphmatches ( sc , test -> sc , layer ) ) return ( test -> sc ) ;
 }
 else if ( sc -> unicodeenc != - 1 ) {
 hash = sc -> unicodeenc & 0xffff ;
 for ( test = ( * uhash ) [ hash ] ;
 test != NULL ;
 test = test -> next ) if ( glyphmatches ( sc , test -> sc , layer ) ) return ( test -> sc ) ;
 }
 for ( alt = sc -> altuni ;
 alt != NULL ;
 alt = alt -> next ) {
 hash = alt -> unienc & 0xffff ;
 for ( test = ( * uhash ) [ hash ] ;
 test != NULL ;
 test = test -> next ) if ( glyphmatches ( sc , test -> sc , layer ) ) return ( test -> sc ) ;
 }
 return ( NULL ) ;
 }