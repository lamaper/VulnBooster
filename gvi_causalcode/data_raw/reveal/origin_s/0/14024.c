int GetCertificateFailure ( JNIEnv * env , const JavaParamRef < jclass > & obj , const JavaParamRef < jobject > & java_web_contents ) {
 enum CertificateFailure {
 NONE = 0 , CERTIFICATE_FAIL_UNSPECIFIED = 1 , CERTIFICATE_FAIL_UNTRUSTED = 2 , CERTIFICATE_FAIL_REVOKED = 3 , CERTIFICATE_FAIL_NOT_YET_VALID = 4 , CERTIFICATE_FAIL_EXPIRED = 5 , CERTIFICATE_FAIL_UNABLE_TO_CHECK_REVOCATION_STATUS = 6 , }
 ;
 content : : WebContents * web_contents = content : : WebContents : : FromJavaWebContents ( java_web_contents ) ;
 content : : NavigationEntry * entry = web_contents -> GetController ( ) . GetVisibleEntry ( ) ;
 if ( ! entry ) return NONE ;
 const content : : SSLStatus & ssl = entry -> GetSSL ( ) ;
 if ( ssl . certificate && entry -> GetURL ( ) . SchemeIsCryptographic ( ) ) {
 if ( net : : IsCertStatusError ( ssl . cert_status ) ) {
 if ( ssl . cert_status & net : : CERT_STATUS_AUTHORITY_INVALID ) {
 return CERTIFICATE_FAIL_UNTRUSTED ;
 }
 if ( ssl . cert_status & net : : CERT_STATUS_REVOKED ) {
 return CERTIFICATE_FAIL_REVOKED ;
 }
 if ( ssl . cert_status & net : : CERT_STATUS_DATE_INVALID ) {
 return CERTIFICATE_FAIL_EXPIRED ;
 }
 if ( ssl . cert_status & net : : CERT_STATUS_UNABLE_TO_CHECK_REVOCATION ) {
 return CERTIFICATE_FAIL_UNABLE_TO_CHECK_REVOCATION_STATUS ;
 }
 return CERTIFICATE_FAIL_UNSPECIFIED ;
 }
 if ( ssl . content_status & content : : SSLStatus : : DISPLAYED_INSECURE_CONTENT || ssl . content_status & content : : SSLStatus : : DISPLAYED_CONTENT_WITH_CERT_ERRORS ) {
 return CERTIFICATE_FAIL_UNSPECIFIED ;
 }
 }
 return NONE ;
 }