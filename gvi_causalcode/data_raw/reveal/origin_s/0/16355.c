TEST_F ( NativeBackendLibsecretTest , RemoveNonexistentLogin ) {
 NativeBackendLibsecret backend ( 42 ) ;
 VerifiedAdd ( & backend , form_google_ ) ;
 EXPECT_EQ ( 1u , global_mock_libsecret_items -> size ( ) ) ;
 if ( ! global_mock_libsecret_items -> empty ( ) ) CheckMockSecretItem ( ( * global_mock_libsecret_items ) [ 0 ] , form_google_ , "chrome-42" ) ;
 PasswordStoreChangeList changes ;
 EXPECT_TRUE ( backend . RemoveLogin ( form_isc_ , & changes ) ) ;
 CheckPasswordChanges ( PasswordStoreChangeList ( ) , changes ) ;
 ScopedVector < autofill : : PasswordForm > form_list ;
 EXPECT_TRUE ( backend . GetAutofillableLogins ( & form_list ) ) ;
 EXPECT_EQ ( 1u , form_list . size ( ) ) ;
 form_list . clear ( ) ;
 EXPECT_EQ ( 1u , global_mock_libsecret_items -> size ( ) ) ;
 if ( ! global_mock_libsecret_items -> empty ( ) ) CheckMockSecretItem ( ( * global_mock_libsecret_items ) [ 0 ] , form_google_ , "chrome-42" ) ;
 }