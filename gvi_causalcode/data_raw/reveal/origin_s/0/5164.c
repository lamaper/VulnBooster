METHOD ( certificate_t , get_encoding , bool , private_x509_cert_t * this , cred_encoding_type_t type , chunk_t * encoding ) {
 if ( type == CERT_ASN1_DER ) {
 * encoding = chunk_clone ( this -> encoding ) ;
 return TRUE ;
 }
 return lib -> encoding -> encode ( lib -> encoding , type , NULL , encoding , CRED_PART_X509_ASN1_DER , this -> encoding , CRED_PART_END ) ;
 }