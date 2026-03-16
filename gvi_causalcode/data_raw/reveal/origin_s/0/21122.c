TEST_F ( NativeBackendLibsecretTest , BasicRemoveLogin ) {
 NativeBackendLibsecret backend ( 42 ) ;
 VerifiedAdd ( & backend , form_google_ ) ;
 EXPECT_EQ ( 1u , global_mock_libsecret_items -> size ( ) ) ;
 if ( ! global_mock_libsecret_items -> empty ( ) ) CheckMockSecretItem ( ( * global_mock_libsecret_items ) [ 0 ] , form_google_ , "chrome-42" ) ;
 VerifiedRemove ( & backend , form_google_ ) ;
 EXPECT_TRUE ( global_mock_libsecret_items -> empty ( ) ) ;
 }