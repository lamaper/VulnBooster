static void HandleType3Reference ( IO * wrapper , EntityChar * ec , real transform [ 6 ] , char * tokbuf , int toksize ) {
 int tok ;
 real dval ;
 char * glyphname ;
 RefChar * ref ;
 tok = nextpstoken ( wrapper , & dval , tokbuf , toksize ) ;
 if ( strcmp ( tokbuf , "get" ) != 0 ) return ;
 tok = nextpstoken ( wrapper , & dval , tokbuf , toksize ) ;
 if ( tok != pt_namelit ) return ;
 glyphname = copy ( tokbuf ) ;
 tok = nextpstoken ( wrapper , & dval , tokbuf , toksize ) ;
 if ( strcmp ( tokbuf , "get" ) != 0 ) {
 free ( glyphname ) ;
 return ;
 }
 tok = nextpstoken ( wrapper , & dval , tokbuf , toksize ) ;
 if ( strcmp ( tokbuf , "exec" ) != 0 ) {
 free ( glyphname ) ;
 return ;
 }
 ref = RefCharCreate ( ) ;
 memcpy ( ref -> transform , transform , sizeof ( ref -> transform ) ) ;
 ref -> sc = ( SplineChar * ) glyphname ;
 ref -> next = ec -> refs ;
 ec -> refs = ref ;
 }