TEST_F ( NativeBackendLibsecretTest , ReadDuplicateForms ) {
 NativeBackendLibsecret backend ( 42 ) ;
 const char unique_string [ ] = "unique_unique_string" ;
 const char unique_string_replacement [ ] = "uniKue_unique_string" ;
 form_google_ . origin = GURL ( std : : string ( "http://www.google.com/" ) + unique_string ) ;
 VerifiedAdd ( & backend , form_google_ ) ;
 form_google_ . origin = GURL ( std : : string ( "http://www.google.com/" ) + unique_string_replacement ) ;
 VerifiedAdd ( & backend , form_google_ ) ;
 ASSERT_EQ ( 2u , global_mock_libsecret_items -> size ( ) ) ;
 gpointer item_value = g_hash_table_lookup ( global_mock_libsecret_items -> front ( ) -> attributes , "origin_url" ) ;
 ASSERT_TRUE ( item_value ) ;
 char * substr = strstr ( static_cast < char * > ( item_value ) , unique_string ) ;
 ASSERT_TRUE ( substr ) ;
 ASSERT_EQ ( strlen ( unique_string ) , strlen ( unique_string_replacement ) ) ;
 strncpy ( substr , unique_string_replacement , strlen ( unique_string ) ) ;
 ScopedVector < autofill : : PasswordForm > form_list ;
 EXPECT_TRUE ( backend . GetAutofillableLogins ( & form_list ) ) ;
 EXPECT_EQ ( 1u , form_list . size ( ) ) ;
 EXPECT_EQ ( form_google_ , * form_list [ 0 ] ) ;
 EXPECT_EQ ( 1u , global_mock_libsecret_items -> size ( ) ) ;
 if ( ! global_mock_libsecret_items -> empty ( ) ) {
 CheckMockSecretItem ( ( * global_mock_libsecret_items ) [ 0 ] , form_google_ , "chrome-42" ) ;
 }
 }