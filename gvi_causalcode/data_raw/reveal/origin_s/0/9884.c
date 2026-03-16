static const char * * slirp_dnssearch ( const StringList * dnsname ) {
 const StringList * c = dnsname ;
 size_t i = 0 , num_opts = 0 ;
 const char * * ret ;
 while ( c ) {
 num_opts ++ ;
 c = c -> next ;
 }
 if ( num_opts == 0 ) {
 return NULL ;
 }
 ret = g_malloc ( ( num_opts + 1 ) * sizeof ( * ret ) ) ;
 c = dnsname ;
 while ( c ) {
 ret [ i ++ ] = c -> value -> str ;
 c = c -> next ;
 }
 ret [ i ] = NULL ;
 return ret ;
 }