TEST_F ( NativeBackendLibsecretTest , FetchFederatedCredential ) {
 other_auth_ . signon_realm = "federation://www.example.com/google.com" ;
 other_auth_ . federation_origin = url : : Origin ( GURL ( "https://google.com/" ) ) ;
 EXPECT_TRUE ( CheckCredentialAvailability ( other_auth_ , GURL ( "http://www.example.com/" ) , PasswordForm : : SCHEME_HTML , nullptr ) ) ;
 }