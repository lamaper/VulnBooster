TEST_F ( NativeBackendLibsecretTest , GetAllLogins ) {
 NativeBackendLibsecret backend ( 42 ) ;
 VerifiedAdd ( & backend , form_google_ ) ;
 VerifiedAdd ( & backend , form_facebook_ ) ;
 ScopedVector < autofill : : PasswordForm > form_list ;
 EXPECT_TRUE ( backend . GetAllLogins ( & form_list ) ) ;
 ASSERT_EQ ( 2u , form_list . size ( ) ) ;
 EXPECT_THAT ( form_list , UnorderedElementsAre ( Pointee ( form_google_ ) , Pointee ( form_facebook_ ) ) ) ;
 }