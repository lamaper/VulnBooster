int ztoken_scanner_options ( const ref * upref , int old_options ) {
 int options = old_options ;
 int i ;
 for ( i = 0 ;
 i < countof ( named_options ) ;
 ++ i ) {
 const named_scanner_option_t * pnso = & named_options [ i ] ;
 ref * ppcproc ;
 int code = dict_find_string ( upref , pnso -> pname , & ppcproc ) ;
 if ( code >= 0 ) {
 if ( r_has_type ( ppcproc , t_null ) ) options &= ~ pnso -> option ;
 else options |= pnso -> option ;
 }
 }
 return options ;
 }