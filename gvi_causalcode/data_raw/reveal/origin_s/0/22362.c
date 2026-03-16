static void SCInterpretPS ( FILE * ps , SplineChar * sc ) {
 EntityChar ec ;
 real dval ;
 char tokbuf [ 10 ] ;
 IO wrapper ;
 int ch ;
 while ( isspace ( ch = getc ( ps ) ) ) ;
 ungetc ( ch , ps ) ;
 memset ( & wrapper , 0 , sizeof ( wrapper ) ) ;
 wrapper . advance_width = UNDEFINED_WIDTH ;
 if ( ch != '<' ) {
 pushio ( & wrapper , ps , NULL , 0 ) ;
 if ( nextpstoken ( & wrapper , & dval , tokbuf , sizeof ( tokbuf ) ) != pt_opencurly ) LogError ( _ ( "We don't understand this font\n" ) ) ;
 }
 else {
 ( void ) getc ( ps ) ;
 pushfogio ( & wrapper , ps ) ;
 }
 memset ( & ec , '\0' , sizeof ( ec ) ) ;
 ec . fromtype3 = true ;
 ec . sc = sc ;
 _InterpretPS ( & wrapper , & ec , NULL ) ;
 sc -> width = ec . width ;
 sc -> layer_cnt = 1 ;
 SCAppendEntityLayers ( sc , ec . splines ) ;
 if ( sc -> layer_cnt == 1 ) ++ sc -> layer_cnt ;
 sc -> layers [ ly_fore ] . refs = revrefs ( ec . refs ) ;
 free ( wrapper . top ) ;
 }