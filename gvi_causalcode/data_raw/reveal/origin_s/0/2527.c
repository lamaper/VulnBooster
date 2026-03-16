TEST ( ExtensionCSPValidator , IsSandboxed ) {
 EXPECT_FALSE ( ContentSecurityPolicyIsSandboxed ( std : : string ( ) , Manifest : : TYPE_EXTENSION ) ) ;
 EXPECT_FALSE ( ContentSecurityPolicyIsSandboxed ( "img-src https://google.com" , Manifest : : TYPE_EXTENSION ) ) ;
 EXPECT_TRUE ( ContentSecurityPolicyIsSandboxed ( "sandbox" , Manifest : : TYPE_EXTENSION ) ) ;
 EXPECT_TRUE ( ContentSecurityPolicyIsSandboxed ( "sandbox allow-scripts" , Manifest : : TYPE_EXTENSION ) ) ;
 EXPECT_FALSE ( ContentSecurityPolicyIsSandboxed ( "sandbox allow-same-origin" , Manifest : : TYPE_EXTENSION ) ) ;
 EXPECT_TRUE ( ContentSecurityPolicyIsSandboxed ( "sandbox;
 img-src https://google.com" , Manifest : : TYPE_EXTENSION ) ) ;
 EXPECT_TRUE ( ContentSecurityPolicyIsSandboxed ( "sandbox allow-top-navigation" , Manifest : : TYPE_EXTENSION ) ) ;
 EXPECT_FALSE ( ContentSecurityPolicyIsSandboxed ( "sandbox allow-top-navigation" , Manifest : : TYPE_PLATFORM_APP ) ) ;
 EXPECT_TRUE ( ContentSecurityPolicyIsSandboxed ( "sandbox allow-popups" , Manifest : : TYPE_EXTENSION ) ) ;
 EXPECT_TRUE ( ContentSecurityPolicyIsSandboxed ( "sandbox allow-popups" , Manifest : : TYPE_PLATFORM_APP ) ) ;
 }