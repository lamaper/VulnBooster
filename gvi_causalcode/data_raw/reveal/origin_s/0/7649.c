TEST ( PasswordManagerUtil , TrimUsernameOnlyCredentials ) {
 ScopedVector < autofill : : PasswordForm > forms , expected_forms ;
 forms . push_back ( new autofill : : PasswordForm ( GetTestAndroidCredentials ( kTestAndroidRealm ) ) ) ;
 expected_forms . push_back ( new autofill : : PasswordForm ( GetTestAndroidCredentials ( kTestAndroidRealm ) ) ) ;
 autofill : : PasswordForm username_only ;
 username_only . scheme = autofill : : PasswordForm : : SCHEME_USERNAME_ONLY ;
 username_only . signon_realm = kTestAndroidRealm ;
 username_only . username_value = base : : ASCIIToUTF16 ( kTestUsername2 ) ;
 forms . push_back ( new autofill : : PasswordForm ( username_only ) ) ;
 username_only . federation_origin = url : : Origin ( GURL ( kTestFederationURL ) ) ;
 username_only . skip_zero_click = false ;
 forms . push_back ( new autofill : : PasswordForm ( username_only ) ) ;
 username_only . skip_zero_click = true ;
 expected_forms . push_back ( new autofill : : PasswordForm ( username_only ) ) ;
 password_manager_util : : TrimUsernameOnlyCredentials ( & forms ) ;
 EXPECT_THAT ( forms . get ( ) , UnorderedPasswordFormElementsAre ( expected_forms . get ( ) ) ) ;
 }