static bool iswheel ( const char * username ) {
 struct group * grp ;
 grp = getgrnam ( "wheel" ) ;
 if ( ( NULL == grp ) || ( NULL == grp -> gr_mem ) ) {
 return false ;
 }
 return is_on_list ( grp -> gr_mem , username ) ;
 }