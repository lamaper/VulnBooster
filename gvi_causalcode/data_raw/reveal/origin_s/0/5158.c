TEST_F ( NativeBackendLibsecretTest , BasicUpdateLogin ) {
 NativeBackendLibsecret backend ( 42 ) ;
 VerifiedAdd ( & backend , form_google_ ) ;
 PasswordForm new_form_google ( form_google_ ) ;
 new_form_google . times_used = 1 ;
 new_form_google . action = GURL ( "http://www.google.com/different/login" ) ;
 EXPECT_EQ ( 1u , global_mock_libsecret_items -> size ( ) ) ;
 if ( ! global_mock_libsecret_items -> empty ( ) ) {
 CheckMockSecretItem ( ( * global_mock_libsecret_items ) [ 0 ] , form_google_ , "chrome-42" ) ;
 }
 VerifiedUpdate ( & backend , new_form_google ) ;
 EXPECT_EQ ( 1u , global_mock_libsecret_items -> size ( ) ) ;
 if ( ! global_mock_libsecret_items -> empty ( ) ) CheckMockSecretItem ( ( * global_mock_libsecret_items ) [ 0 ] , new_form_google , "chrome-42" ) ;
 }