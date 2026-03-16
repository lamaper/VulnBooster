TEST_F ( BrowsingDataRemoverImplTest , RemoveDownloadsByTimeOnly ) {
 RemoveDownloadsTester tester ( GetBrowserContext ( ) ) ;
 base : : Callback < bool ( const GURL & ) > filter = BrowsingDataFilterBuilder : : BuildNoopFilter ( ) ;
 EXPECT_CALL ( * tester . download_manager ( ) , RemoveDownloadsByURLAndTime ( ProbablySameFilter ( filter ) , _ , _ ) ) ;
 BlockUntilBrowsingDataRemoved ( base : : Time ( ) , base : : Time : : Max ( ) , BrowsingDataRemover : : REMOVE_DOWNLOADS , false ) ;
 }