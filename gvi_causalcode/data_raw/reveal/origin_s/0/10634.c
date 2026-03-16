TEST_F ( BrowsingDataRemoverImplTest , ClearHttpAuthCache_RemoveCookies ) {
 net : : HttpNetworkSession * http_session = content : : BrowserContext : : GetDefaultStoragePartition ( GetBrowserContext ( ) ) -> GetURLRequestContext ( ) -> GetURLRequestContext ( ) -> http_transaction_factory ( ) -> GetSession ( ) ;
 DCHECK ( http_session ) ;
 net : : HttpAuthCache * http_auth_cache = http_session -> http_auth_cache ( ) ;
 http_auth_cache -> Add ( kOrigin1 , kTestRealm , net : : HttpAuth : : AUTH_SCHEME_BASIC , "test challenge" , net : : AuthCredentials ( base : : ASCIIToUTF16 ( "foo" ) , base : : ASCIIToUTF16 ( "bar" ) ) , "/" ) ;
 CHECK ( http_auth_cache -> Lookup ( kOrigin1 , kTestRealm , net : : HttpAuth : : AUTH_SCHEME_BASIC ) ) ;
 BlockUntilBrowsingDataRemoved ( base : : Time ( ) , base : : Time : : Max ( ) , BrowsingDataRemover : : REMOVE_COOKIES , false ) ;
 EXPECT_EQ ( nullptr , http_auth_cache -> Lookup ( kOrigin1 , kTestRealm , net : : HttpAuth : : AUTH_SCHEME_BASIC ) ) ;
 }