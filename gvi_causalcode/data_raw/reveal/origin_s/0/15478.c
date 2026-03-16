static private_x509_cert_t * create_empty ( void ) {
 private_x509_cert_t * this ;
 INIT ( this , . public = {
 . interface = {
 . interface = {
 . get_type = _get_type , . get_subject = _get_subject , . get_issuer = _get_issuer , . has_subject = _has_subject , . has_issuer = _has_issuer , . issued_by = _issued_by , . get_public_key = _get_public_key , . get_validity = _get_validity , . get_encoding = _get_encoding , . equals = _equals , . get_ref = _get_ref , . destroy = _destroy , }
 , . get_flags = _get_flags , . get_serial = _get_serial , . get_subjectKeyIdentifier = _get_subjectKeyIdentifier , . get_authKeyIdentifier = _get_authKeyIdentifier , . get_constraint = _get_constraint , . create_subjectAltName_enumerator = _create_subjectAltName_enumerator , . create_crl_uri_enumerator = _create_crl_uri_enumerator , . create_ocsp_uri_enumerator = _create_ocsp_uri_enumerator , . create_ipAddrBlock_enumerator = _create_ipAddrBlock_enumerator , . create_name_constraint_enumerator = _create_name_constraint_enumerator , . create_cert_policy_enumerator = _create_cert_policy_enumerator , . create_policy_mapping_enumerator = _create_policy_mapping_enumerator , }
 , }
 , . version = 1 , . subjectAltNames = linked_list_create ( ) , . crl_uris = linked_list_create ( ) , . ocsp_uris = linked_list_create ( ) , . ipAddrBlocks = linked_list_create ( ) , . permitted_names = linked_list_create ( ) , . excluded_names = linked_list_create ( ) , . cert_policies = linked_list_create ( ) , . policy_mappings = linked_list_create ( ) , . pathLenConstraint = X509_NO_CONSTRAINT , . require_explicit = X509_NO_CONSTRAINT , . inhibit_mapping = X509_NO_CONSTRAINT , . inhibit_any = X509_NO_CONSTRAINT , . ref = 1 , ) ;
 return this ;
 }