static void printarray ( struct pskeydict * dict ) {
 int i ;
 printf ( "[" ) ;
 for ( i = 0 ;
 i < dict -> cnt ;
 ++ i ) {
 switch ( dict -> entries [ i ] . type ) {
 case ps_num : printf ( "%g" , ( double ) dict -> entries [ i ] . u . val ) ;
 break ;
 case ps_bool : printf ( "%s" , dict -> entries [ i ] . u . tf ? "true" : "false" ) ;
 break ;
 case ps_string : case ps_instr : case ps_lit : printf ( dict -> entries [ i ] . type == ps_lit ? "/" : dict -> entries [ i ] . type == ps_string ? "(" : "{
" ) ;
 printf ( "%s" , dict -> entries [ i ] . u . str ) ;
 printf ( dict -> entries [ i ] . type == ps_lit ? "" : dict -> entries [ i ] . type == ps_string ? ")" : "}
" ) ;
 break ;
 case ps_array : printarray ( & dict -> entries [ i ] . u . dict ) ;
 break ;
 case ps_void : printf ( "-- void --" ) ;
 break ;
 default : printf ( "-- nostringval --" ) ;
 break ;
 }
 printf ( " " ) ;
 }
 printf ( "]" ) ;
 }