TEST_F ( NativeBackendLibsecretTest , AddDuplicateLogin ) {
 NativeBackendLibsecret backend ( 42 ) ;
 VerifiedAdd ( & backend , form_google_ ) ;
 PasswordStoreChangeList expected_changes ;
 expected_changes . push_back ( PasswordStoreChange ( PasswordStoreChange : : REMOVE , form_google_ ) ) ;
 form_google_ . times_used ++ ;
 form_google_ . submit_element = UTF8ToUTF16 ( "submit2" ) ;
 expected_changes . push_back ( PasswordStoreChange ( PasswordStoreChange : : ADD , form_google_ ) ) ;
 PasswordStoreChangeList actual_changes = backend . AddLogin ( form_google_ ) ;
 CheckPasswordChanges ( expected_changes , actual_changes ) ;
 EXPECT_EQ ( 1u , global_mock_libsecret_items -> size ( ) ) ;
 if ( ! global_mock_libsecret_items -> empty ( ) ) CheckMockSecretItem ( ( * global_mock_libsecret_items ) [ 0 ] , form_google_ , "chrome-42" ) ;
 }