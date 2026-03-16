METHOD ( x509_t , get_subjectKeyIdentifier , chunk_t , private_x509_cert_t * this ) {
 if ( this -> subjectKeyIdentifier . ptr ) {
 return this -> subjectKeyIdentifier ;
 }
 else {
 chunk_t fingerprint ;
 if ( this -> public_key -> get_fingerprint ( this -> public_key , KEYID_PUBKEY_SHA1 , & fingerprint ) ) {
 return fingerprint ;
 }
 else {
 return chunk_empty ;
 }
 }
 }