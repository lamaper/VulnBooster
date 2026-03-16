TEST_F ( TemplateURLTest , GenerateKeyword ) {
 std : : string accept_languages = "en,ru" ;
 ASSERT_EQ ( ASCIIToUTF16 ( "foo" ) , TemplateURL : : GenerateKeyword ( GURL ( "http://foo" ) , accept_languages ) ) ;
 ASSERT_EQ ( ASCIIToUTF16 ( "foo" ) , TemplateURL : : GenerateKeyword ( GURL ( "http://www.foo" ) , accept_languages ) ) ;
 ASSERT_EQ ( ASCIIToUTF16 ( "blah" ) , TemplateURL : : GenerateKeyword ( GURL ( "http://blah/" ) , accept_languages ) ) ;
 ASSERT_EQ ( ASCIIToUTF16 ( "www" ) , TemplateURL : : GenerateKeyword ( GURL ( "http://www." ) , accept_languages ) ) ;
 ASSERT_EQ ( base : : UTF8ToUTF16 ( "\xd0\xb0\xd0\xb1\xd0\xb2" ) , TemplateURL : : GenerateKeyword ( GURL ( "http://xn--80acd" ) , accept_languages ) ) ;
 }