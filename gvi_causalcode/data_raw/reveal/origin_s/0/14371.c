TEST ( ExtensionCSPValidator , IsLegal ) {
 EXPECT_TRUE ( ContentSecurityPolicyIsLegal ( "foo" ) ) ;
 EXPECT_TRUE ( ContentSecurityPolicyIsLegal ( "default-src 'self';
 script-src http://www.google.com" ) ) ;
 EXPECT_FALSE ( ContentSecurityPolicyIsLegal ( "default-src 'self';
\nscript-src http://www.google.com" ) ) ;
 EXPECT_FALSE ( ContentSecurityPolicyIsLegal ( "default-src 'self';
\rscript-src http://www.google.com" ) ) ;
 EXPECT_FALSE ( ContentSecurityPolicyIsLegal ( "default-src 'self';
,script-src http://www.google.com" ) ) ;
 }