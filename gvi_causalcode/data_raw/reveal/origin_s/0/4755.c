void InitializeSchemeWhitelist ( SchemeSet * whitelist , const SchemeSet & client_schemes_to_whitelist ) {
 DCHECK ( whitelist ) ;
 if ( ! whitelist -> empty ( ) ) return ;
 whitelist -> insert ( client_schemes_to_whitelist . begin ( ) , client_schemes_to_whitelist . end ( ) ) ;
 whitelist -> insert ( std : : string ( url : : kAboutScheme ) ) ;
 whitelist -> insert ( std : : string ( url : : kFileScheme ) ) ;
 whitelist -> insert ( std : : string ( url : : kFtpScheme ) ) ;
 whitelist -> insert ( std : : string ( url : : kHttpScheme ) ) ;
 whitelist -> insert ( std : : string ( url : : kHttpsScheme ) ) ;
 whitelist -> insert ( std : : string ( url : : kMailToScheme ) ) ;
 }