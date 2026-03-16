METHOD ( certificate_t , issued_by , bool , private_x509_cert_t * this , certificate_t * issuer , signature_scheme_t * schemep ) {
 public_key_t * key ;
 signature_scheme_t scheme ;
 bool valid ;
 x509_t * x509 = ( x509_t * ) issuer ;
 if ( & this -> public . interface . interface == issuer ) {
 if ( this -> flags & X509_SELF_SIGNED ) {
 return TRUE ;
 }
 }
 else {
 if ( issuer -> get_type ( issuer ) != CERT_X509 ) {
 return FALSE ;
 }
 if ( ! ( x509 -> get_flags ( x509 ) & X509_CA ) ) {
 return FALSE ;
 }
 }
 if ( ! this -> issuer -> equals ( this -> issuer , issuer -> get_subject ( issuer ) ) ) {
 return FALSE ;
 }
 scheme = signature_scheme_from_oid ( this -> algorithm ) ;
 if ( scheme == SIGN_UNKNOWN ) {
 return FALSE ;
 }
 key = issuer -> get_public_key ( issuer ) ;
 if ( ! key ) {
 return FALSE ;
 }
 valid = key -> verify ( key , scheme , this -> tbsCertificate , this -> signature ) ;
 key -> destroy ( key ) ;
 if ( valid && schemep ) {
 * schemep = scheme ;
 }
 return valid ;
 }