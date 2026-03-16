TEST_F ( NativeBackendLibsecretTest , PSLMatchingDisabledDomains ) {
 EXPECT_FALSE ( CheckCredentialAvailability ( form_google_ , GURL ( "http://one.google.com/" ) , PasswordForm : : SCHEME_HTML , nullptr ) ) ;
 }