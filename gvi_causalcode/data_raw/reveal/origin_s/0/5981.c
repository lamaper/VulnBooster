void PSFontInterpretPS ( FILE * ps , struct charprocs * cp , char * * encoding ) {
 char tokbuf [ 100 ] ;
 int tok , i , j ;
 real dval ;
 SplineChar * sc ;
 EntityChar dummy ;
 RefChar * p , * ref , * next ;
 IO wrapper ;
 wrapper . top = NULL ;
 wrapper . advance_width = UNDEFINED_WIDTH ;
 pushio ( & wrapper , ps , NULL , 0 ) ;
 while ( ( tok = nextpstoken ( & wrapper , & dval , tokbuf , sizeof ( tokbuf ) ) ) != pt_eof && tok != pt_end ) {
 if ( tok == pt_namelit ) {
 if ( cp -> next >= cp -> cnt ) {
 ++ cp -> cnt ;
 cp -> keys = realloc ( cp -> keys , cp -> cnt * sizeof ( char * ) ) ;
 cp -> values = realloc ( cp -> values , cp -> cnt * sizeof ( char * ) ) ;
 }
 if ( cp -> next < cp -> cnt ) {
 sc = SplineCharCreate ( 2 ) ;
 cp -> keys [ cp -> next ] = copy ( tokbuf ) ;
 cp -> values [ cp -> next ++ ] = sc ;
 sc -> name = copy ( tokbuf ) ;
 SCInterpretPS ( ps , sc ) ;
 ff_progress_next ( ) ;
 }
 else {
 memset ( & dummy , 0 , sizeof ( dummy ) ) ;
 dummy . fromtype3 = true ;
 InterpretPS ( ps , NULL , & dummy , NULL ) ;
 }
 }
 }
 free ( wrapper . top ) ;
 for ( i = 0 ;
 i < cp -> next ;
 ++ i ) {
 for ( p = NULL , ref = cp -> values [ i ] -> layers [ ly_fore ] . refs ;
 ref != NULL ;
 ref = next ) {
 char * refname = ( char * ) ( ref -> sc ) ;
 next = ref -> next ;
 if ( ref -> sc == NULL ) refname = encoding [ ref -> orig_pos ] ;
 for ( j = 0 ;
 j < cp -> next ;
 ++ j ) if ( strcmp ( cp -> keys [ j ] , refname ) == 0 ) break ;
 free ( ref -> sc ) ;
 if ( j != cp -> next ) {
 ref -> sc = cp -> values [ j ] ;
 SCMakeDependent ( cp -> values [ i ] , ref -> sc ) ;
 ref -> adobe_enc = getAdobeEnc ( ref -> sc -> name ) ;
 ref -> checked = true ;
 p = ref ;
 }
 else {
 if ( p == NULL ) cp -> values [ i ] -> layers [ ly_fore ] . refs = next ;
 else p -> next = next ;
 ref -> next = NULL ;
 RefCharFree ( ref ) ;
 }
 }
 }
 }