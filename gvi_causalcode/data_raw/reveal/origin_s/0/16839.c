TEST_F ( NativeBackendLibsecretTest , AndroidCredentials ) {
 NativeBackendLibsecret backend ( 42 ) ;
 backend . Init ( ) ;
 PasswordForm observed_android_form ;
 observed_android_form . scheme = PasswordForm : : SCHEME_HTML ;
 observed_android_form . signon_realm = "android://7x7IDboo8u9YKraUsbmVkuf1-@net.rateflix.app/" ;
 PasswordForm saved_android_form = observed_android_form ;
 saved_android_form . username_value = base : : UTF8ToUTF16 ( "randomusername" ) ;
 saved_android_form . password_value = base : : UTF8ToUTF16 ( "password" ) ;
 saved_android_form . date_created = base : : Time : : Now ( ) ;
 VerifiedAdd ( & backend , saved_android_form ) ;
 ScopedVector < autofill : : PasswordForm > form_list ;
 EXPECT_TRUE ( backend . GetAutofillableLogins ( & form_list ) ) ;
 EXPECT_EQ ( 1u , form_list . size ( ) ) ;
 EXPECT_EQ ( saved_android_form , * form_list [ 0 ] ) ;
 }