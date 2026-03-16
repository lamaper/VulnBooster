TEST_F ( BrowsingDataRemoverImplTest , RemoveDownloadsByOrigin ) {
 RemoveDownloadsTester tester ( GetBrowserContext ( ) ) ;
 std : : unique_ptr < BrowsingDataFilterBuilder > builder ( BrowsingDataFilterBuilder : : Create ( BrowsingDataFilterBuilder : : WHITELIST ) ) ;
 builder -> AddRegisterableDomain ( kTestRegisterableDomain1 ) ;
 base : : Callback < bool ( const GURL & ) > filter = builder -> BuildGeneralFilter ( ) ;
 EXPECT_CALL ( * tester . download_manager ( ) , RemoveDownloadsByURLAndTime ( ProbablySameFilter ( filter ) , _ , _ ) ) ;
 BlockUntilOriginDataRemoved ( base : : Time ( ) , base : : Time : : Max ( ) , BrowsingDataRemover : : REMOVE_DOWNLOADS , std : : move ( builder ) ) ;
 }