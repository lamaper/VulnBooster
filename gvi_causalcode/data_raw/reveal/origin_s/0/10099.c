TEST_F ( NativeBackendLibsecretTest , PSLMatchingPositive ) {
 PasswordForm result ;
 const GURL kMobileURL ( "http://m.facebook.com/" ) ;
 EXPECT_TRUE ( CheckCredentialAvailability ( form_facebook_ , kMobileURL , PasswordForm : : SCHEME_HTML , & result ) ) ;
 EXPECT_EQ ( form_facebook_ . origin , result . origin ) ;
 EXPECT_EQ ( form_facebook_ . signon_realm , result . signon_realm ) ;
 }