METHOD ( certificate_t , has_subject , id_match_t , private_x509_cert_t * this , identification_t * subject ) {
 identification_t * current ;
 enumerator_t * enumerator ;
 id_match_t match , best ;
 chunk_t encoding ;
 if ( subject -> get_type ( subject ) == ID_KEY_ID ) {
 encoding = subject -> get_encoding ( subject ) ;
 if ( this -> encoding_hash . len && chunk_equals ( this -> encoding_hash , encoding ) ) {
 return ID_MATCH_PERFECT ;
 }
 if ( this -> subjectKeyIdentifier . len && chunk_equals ( this -> subjectKeyIdentifier , encoding ) ) {
 return ID_MATCH_PERFECT ;
 }
 if ( this -> public_key && this -> public_key -> has_fingerprint ( this -> public_key , encoding ) ) {
 return ID_MATCH_PERFECT ;
 }
 if ( chunk_equals ( this -> serialNumber , encoding ) ) {
 return ID_MATCH_PERFECT ;
 }
 }
 best = this -> subject -> matches ( this -> subject , subject ) ;
 enumerator = this -> subjectAltNames -> create_enumerator ( this -> subjectAltNames ) ;
 while ( enumerator -> enumerate ( enumerator , & current ) ) {
 match = current -> matches ( current , subject ) ;
 if ( match > best ) {
 best = match ;
 }
 }
 enumerator -> destroy ( enumerator ) ;
 return best ;
 }