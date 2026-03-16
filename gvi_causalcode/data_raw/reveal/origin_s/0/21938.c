TEST_F ( NativeBackendLibsecretTest , DisableAutoSignInForOrigins ) {
 NativeBackendLibsecret backend ( 42 ) ;
 backend . Init ( ) ;
 form_google_ . skip_zero_click = false ;
 form_facebook_ . skip_zero_click = false ;
 VerifiedAdd ( & backend , form_google_ ) ;
 VerifiedAdd ( & backend , form_facebook_ ) ;
 EXPECT_EQ ( 2u , global_mock_libsecret_items -> size ( ) ) ;
 for ( const auto & item : * global_mock_libsecret_items ) CheckUint32Attribute ( item , "should_skip_zero_click" , 0 ) ;
 form_google_ . skip_zero_click = true ;
 form_facebook_ . skip_zero_click = true ;
 PasswordStoreChangeList expected_changes ;
 expected_changes . push_back ( PasswordStoreChange ( PasswordStoreChange : : UPDATE , form_facebook_ ) ) ;
 PasswordStoreChangeList changes ;
 EXPECT_TRUE ( backend . DisableAutoSignInForOrigins ( base : : Bind ( & GURL : : operator == , base : : Unretained ( & form_facebook_ . origin ) ) , & changes ) ) ;
 CheckPasswordChanges ( expected_changes , changes ) ;
 EXPECT_EQ ( 2u , global_mock_libsecret_items -> size ( ) ) ;
 CheckStringAttribute ( ( * global_mock_libsecret_items ) [ 0 ] , "origin_url" , form_google_ . origin . spec ( ) ) ;
 CheckUint32Attribute ( ( * global_mock_libsecret_items ) [ 0 ] , "should_skip_zero_click" , 0 ) ;
 CheckStringAttribute ( ( * global_mock_libsecret_items ) [ 1 ] , "origin_url" , form_facebook_ . origin . spec ( ) ) ;
 CheckUint32Attribute ( ( * global_mock_libsecret_items ) [ 1 ] , "should_skip_zero_click" , 1 ) ;
 }