TEST_F ( NativeBackendLibsecretTest , BasicListLogins ) {
 NativeBackendLibsecret backend ( 42 ) ;
 VerifiedAdd ( & backend , form_google_ ) ;
 ScopedVector < autofill : : PasswordForm > form_list ;
 EXPECT_TRUE ( backend . GetAutofillableLogins ( & form_list ) ) ;
 ASSERT_EQ ( 1u , form_list . size ( ) ) ;
 EXPECT_EQ ( form_google_ , * form_list [ 0 ] ) ;
 EXPECT_EQ ( 1u , global_mock_libsecret_items -> size ( ) ) ;
 if ( ! global_mock_libsecret_items -> empty ( ) ) CheckMockSecretItem ( ( * global_mock_libsecret_items ) [ 0 ] , form_google_ , "chrome-42" ) ;
 }