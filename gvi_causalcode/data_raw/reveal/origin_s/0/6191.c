TEST_F ( BrowsingDataRemoverImplTest , EarlyShutdown ) {
 BrowsingDataRemoverImpl * remover = static_cast < BrowsingDataRemoverImpl * > ( BrowsingDataRemoverFactory : : GetForBrowserContext ( GetBrowserContext ( ) ) ) ;
 InspectableCompletionObserver completion_observer ( remover ) ;
 BrowsingDataRemoverCompletionInhibitor completion_inhibitor ;
 remover -> RemoveAndReply ( base : : Time ( ) , base : : Time : : Max ( ) , BrowsingDataRemover : : REMOVE_HISTORY , BrowsingDataHelper : : UNPROTECTED_WEB , & completion_observer ) ;
 completion_inhibitor . BlockUntilNearCompletion ( ) ;
 EXPECT_TRUE ( remover -> is_removing ( ) ) ;
 EXPECT_FALSE ( completion_observer . called ( ) ) ;
 DestroyBrowserContext ( ) ;
 EXPECT_TRUE ( completion_observer . called ( ) ) ;
 completion_inhibitor . ContinueToCompletion ( ) ;
 completion_observer . BlockUntilCompletion ( ) ;
 }