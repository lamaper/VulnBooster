TEST_F ( NativeBackendLibsecretTest , UpdateNonexistentLogin ) {
 NativeBackendLibsecret backend ( 42 ) ;
 VerifiedAdd ( & backend , form_google_ ) ;
 EXPECT_EQ ( 1u , global_mock_libsecret_items -> size ( ) ) ;
 if ( ! global_mock_libsecret_items -> empty ( ) ) {
 CheckMockSecretItem ( ( * global_mock_libsecret_items ) [ 0 ] , form_google_ , "chrome-42" ) ;
 }
 PasswordStoreChangeList changes ;
 EXPECT_TRUE ( backend . UpdateLogin ( form_isc_ , & changes ) ) ;
 CheckPasswordChanges ( PasswordStoreChangeList ( ) , changes ) ;
 EXPECT_EQ ( 1u , global_mock_libsecret_items -> size ( ) ) ;
 if ( ! global_mock_libsecret_items -> empty ( ) ) CheckMockSecretItem ( ( * global_mock_libsecret_items ) [ 0 ] , form_google_ , "chrome-42" ) ;
 }