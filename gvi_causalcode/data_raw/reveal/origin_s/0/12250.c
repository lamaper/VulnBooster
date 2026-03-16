METHOD ( x509_t , get_constraint , u_int , private_x509_cert_t * this , x509_constraint_t type ) {
 switch ( type ) {
 case X509_PATH_LEN : return this -> pathLenConstraint ;
 case X509_REQUIRE_EXPLICIT_POLICY : return this -> require_explicit ;
 case X509_INHIBIT_POLICY_MAPPING : return this -> inhibit_mapping ;
 case X509_INHIBIT_ANY_POLICY : return this -> inhibit_any ;
 default : return X509_NO_CONSTRAINT ;
 }
 }