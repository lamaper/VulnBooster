Encoding * PSSlurpEncodings ( FILE * file ) {
 char * names [ 1024 ] ;
 int32 encs [ 1024 ] ;
 Encoding * item , * head = NULL , * last ;
 char * encname ;
 char tokbuf [ 200 ] ;
 IO wrapper ;
 real dval ;
 size_t i , any ;
 int max , enc , codepointsonly , tok ;
 wrapper . top = NULL ;
 wrapper . advance_width = UNDEFINED_WIDTH ;
 pushio ( & wrapper , file , NULL , 0 ) ;
 while ( ( tok = nextpstoken ( & wrapper , & dval , tokbuf , sizeof ( tokbuf ) ) ) != pt_eof ) {
 encname = NULL ;
 if ( tok == pt_namelit ) {
 encname = copy ( tokbuf ) ;
 tok = nextpstoken ( & wrapper , & dval , tokbuf , sizeof ( tokbuf ) ) ;
 }
 if ( tok != pt_openarray && tok != pt_opencurly ) return ( head ) ;
 for ( i = 0 ;
 i < sizeof ( names ) / sizeof ( names [ 0 ] ) ;
 ++ i ) {
 encs [ i ] = - 1 ;
 names [ i ] = NULL ;
 }
 codepointsonly = CheckCodePointsComment ( & wrapper ) ;
 max = - 1 ;
 any = 0 ;
 for ( i = 0 ;
 ( tok = nextpstoken ( & wrapper , & dval , tokbuf , sizeof ( tokbuf ) ) ) != pt_eof && tok != pt_closearray && tok != pt_closecurly ;
 i ++ ) {
 if ( tok == pt_namelit && i < sizeof ( names ) / sizeof ( names [ 0 ] ) ) {
 max = i ;
 if ( strcmp ( tokbuf , ".notdef" ) == 0 ) {
 encs [ i ] = - 1 ;
 }
 else if ( ( enc = UniFromName ( tokbuf , ui_none , & custom ) ) != - 1 ) {
 encs [ i ] = enc ;
 names [ i ] = copy ( tokbuf ) ;
 any = 1 ;
 }
 else {
 names [ i ] = copy ( tokbuf ) ;
 any = 1 ;
 }
 }
 }
 if ( encname != NULL ) {
 tok = nextpstoken ( & wrapper , & dval , tokbuf , sizeof ( tokbuf ) ) ;
 if ( tok == pt_def ) {
 }
 else {
 }
 }
 if ( max != - 1 ) {
 if ( ++ max < 256 ) max = 256 ;
 item = calloc ( 1 , sizeof ( Encoding ) ) ;
 item -> enc_name = encname ;
 item -> char_cnt = max ;
 item -> unicode = malloc ( max * sizeof ( int32 ) ) ;
 memcpy ( item -> unicode , encs , max * sizeof ( int32 ) ) ;
 if ( any && ! codepointsonly ) {
 item -> psnames = calloc ( max , sizeof ( char * ) ) ;
 memcpy ( item -> psnames , names , max * sizeof ( char * ) ) ;
 }
 else {
 for ( i = 0 ;
 i < max ;
 ++ i ) free ( names [ i ] ) ;
 }
 if ( head == NULL ) head = item ;
 else last -> next = item ;
 last = item ;
 }
 }
 return ( head ) ;
 }