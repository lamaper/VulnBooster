static void SetHomePageRedirectFlag ( url_mapping * new_mapping , URL & new_to_url ) {
 int fromLen , toLen ;
 const char * from_path = new_mapping -> fromURL . path_get ( & fromLen ) ;
 const char * to_path = new_to_url . path_get ( & toLen ) ;
 new_mapping -> homePageRedirect = ( from_path && ! to_path ) ? true : false ;
 }