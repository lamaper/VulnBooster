int wild_case_compare ( CHARSET_INFO * cs , const char * str , const char * wildstr ) {
 reg3 int flag ;
 DBUG_ENTER ( "wild_case_compare" ) ;
 DBUG_PRINT ( "enter" , ( "str: '%s' wildstr: '%s'" , str , wildstr ) ) ;
 while ( * wildstr ) {
 while ( * wildstr && * wildstr != wild_many && * wildstr != wild_one ) {
 if ( * wildstr == wild_prefix && wildstr [ 1 ] ) wildstr ++ ;
 if ( my_toupper ( cs , * wildstr ++ ) != my_toupper ( cs , * str ++ ) ) DBUG_RETURN ( 1 ) ;
 }
 if ( ! * wildstr ) DBUG_RETURN ( * str != 0 ) ;
 if ( * wildstr ++ == wild_one ) {
 if ( ! * str ++ ) DBUG_RETURN ( 1 ) ;
 }
 else {
 if ( ! * wildstr ) DBUG_RETURN ( 0 ) ;
 flag = ( * wildstr != wild_many && * wildstr != wild_one ) ;
 do {
 if ( flag ) {
 char cmp ;
 if ( ( cmp = * wildstr ) == wild_prefix && wildstr [ 1 ] ) cmp = wildstr [ 1 ] ;
 cmp = my_toupper ( cs , cmp ) ;
 while ( * str && my_toupper ( cs , * str ) != cmp ) str ++ ;
 if ( ! * str ) DBUG_RETURN ( 1 ) ;
 }
 if ( wild_case_compare ( cs , str , wildstr ) == 0 ) DBUG_RETURN ( 0 ) ;
 }
 while ( * str ++ ) ;
 DBUG_RETURN ( 1 ) ;
 }
 }
 DBUG_RETURN ( * str != '\0' ) ;
 }