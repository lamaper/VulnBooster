TEST_F ( TemplateURLTest , GenerateKeyword ) {
 ASSERT_EQ ( ASCIIToUTF16 ( "foo" ) , TemplateURL : : GenerateKeyword ( GURL ( "http://foo" ) ) ) ;
 ASSERT_EQ ( ASCIIToUTF16 ( "foo" ) , TemplateURL : : GenerateKeyword ( GURL ( "http://www.foo" ) ) ) ;
 ASSERT_EQ ( ASCIIToUTF16 ( "blah" ) , TemplateURL : : GenerateKeyword ( GURL ( "http://blah/" ) ) ) ;
 ASSERT_EQ ( ASCIIToUTF16 ( "www" ) , TemplateURL : : GenerateKeyword ( GURL ( "http://www." ) ) ) ;
 ASSERT_EQ ( base : : UTF8ToUTF16 ( "\xd0\xb0\xd0\xb1\xd0\xb2" ) , TemplateURL : : GenerateKeyword ( GURL ( "http://xn--80acd" ) ) ) ;
 }