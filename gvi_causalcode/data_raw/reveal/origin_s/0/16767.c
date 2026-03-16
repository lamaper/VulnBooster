static int oc_filter ( Filter * f , int cur , int * max ) {
 int rc = 0 ;
 assert ( f != NULL ) ;
 if ( cur > * max ) * max = cur ;
 switch ( f -> f_choice ) {
 case LDAP_FILTER_PRESENT : if ( f -> f_desc == slap_schema . si_ad_objectClass ) {
 rc = 1 ;
 }
 break ;
 case LDAP_FILTER_AND : case LDAP_FILTER_OR : cur ++ ;
 for ( f = f -> f_and ;
 f ;
 f = f -> f_next ) {
 ( void ) oc_filter ( f , cur , max ) ;
 }
 break ;
 default : break ;
 }
 return rc ;
 }