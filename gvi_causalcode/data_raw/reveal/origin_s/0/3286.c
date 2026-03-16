TEST_F ( NativeBackendLibsecretTest , SomeKeyringAttributesAreMissing ) {
 NativeBackendLibsecret backend ( 42 ) ;
 VerifiedAdd ( & backend , form_google_ ) ;
 EXPECT_EQ ( 1u , global_mock_libsecret_items -> size ( ) ) ;
 ( * global_mock_libsecret_items ) [ 0 ] -> RemoveAttribute ( "avatar_url" ) ;
 ( * global_mock_libsecret_items ) [ 0 ] -> RemoveAttribute ( "times_used" ) ;
 ScopedVector < autofill : : PasswordForm > form_list ;
 EXPECT_TRUE ( backend . GetAutofillableLogins ( & form_list ) ) ;
 EXPECT_EQ ( 1u , form_list . size ( ) ) ;
 EXPECT_EQ ( GURL ( "" ) , form_list [ 0 ] -> icon_url ) ;
 EXPECT_EQ ( 0 , form_list [ 0 ] -> times_used ) ;
 }