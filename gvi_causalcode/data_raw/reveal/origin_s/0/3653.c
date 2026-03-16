int virLogParseFilters ( const char * src , virLogFilterPtr * * filters ) {
 int ret = - 1 ;
 size_t nfilters = 0 ;
 size_t i , count ;
 char * * strings = NULL ;
 virLogFilterPtr filter = NULL ;
 virLogFilterPtr * list = NULL ;
 VIR_DEBUG ( "filters=%s" , src ) ;
 if ( ! ( strings = virStringSplitCount ( src , " " , 0 , & count ) ) ) goto cleanup ;
 for ( i = 0 ;
 i < count ;
 i ++ ) {
 if ( STREQ ( strings [ i ] , "" ) ) continue ;
 if ( ! ( filter = virLogParseFilter ( strings [ i ] ) ) ) goto cleanup ;
 if ( VIR_APPEND_ELEMENT ( list , nfilters , filter ) ) {
 virLogFilterFree ( filter ) ;
 goto cleanup ;
 }
 }
 ret = nfilters ;
 * filters = list ;
 list = NULL ;
 cleanup : virStringListFree ( strings ) ;
 return ret ;
 }