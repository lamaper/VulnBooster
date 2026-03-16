METHOD ( x509_t , create_name_constraint_enumerator , enumerator_t * , private_x509_cert_t * this , bool perm ) {
 if ( perm ) {
 return this -> permitted_names -> create_enumerator ( this -> permitted_names ) ;
 }
 return this -> excluded_names -> create_enumerator ( this -> excluded_names ) ;
 }