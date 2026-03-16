static void unnextch ( int ch , IO * wrapper ) {
 if ( ch == EOF ) return ;
 if ( wrapper -> top == NULL ) LogError ( _ ( "Can't back up with nothing on stack\n" ) ) ;
 else if ( wrapper -> top -> backedup != EOF ) LogError ( _ ( "Attempt to back up twice\n" ) ) ;
 else if ( wrapper -> top -> ps != NULL ) ungetc ( ch , wrapper -> top -> ps ) ;
 else wrapper -> top -> backedup = ch ;
 }