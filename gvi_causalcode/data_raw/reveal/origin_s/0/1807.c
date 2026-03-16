TEST_F ( BrowsingDataRemoverImplTest , MultipleTasksInQuickSuccession ) {
 BrowsingDataRemoverImpl * remover = static_cast < BrowsingDataRemoverImpl * > ( BrowsingDataRemoverFactory : : GetForBrowserContext ( GetBrowserContext ( ) ) ) ;
 EXPECT_FALSE ( remover -> is_removing ( ) ) ;
 int test_removal_masks [ ] = {
 BrowsingDataRemover : : REMOVE_COOKIES , BrowsingDataRemover : : REMOVE_PASSWORDS , BrowsingDataRemover : : REMOVE_COOKIES , BrowsingDataRemover : : REMOVE_COOKIES , BrowsingDataRemover : : REMOVE_COOKIES , BrowsingDataRemover : : REMOVE_HISTORY , BrowsingDataRemover : : REMOVE_HISTORY , BrowsingDataRemover : : REMOVE_HISTORY , BrowsingDataRemover : : REMOVE_COOKIES | BrowsingDataRemover : : REMOVE_HISTORY , BrowsingDataRemover : : REMOVE_COOKIES | BrowsingDataRemover : : REMOVE_HISTORY , BrowsingDataRemover : : REMOVE_COOKIES | BrowsingDataRemover : : REMOVE_HISTORY | BrowsingDataRemover : : REMOVE_PASSWORDS , BrowsingDataRemover : : REMOVE_PASSWORDS , BrowsingDataRemover : : REMOVE_PASSWORDS , }
 ;
 for ( int removal_mask : test_removal_masks ) {
 remover -> Remove ( base : : Time ( ) , base : : Time : : Max ( ) , removal_mask , BrowsingDataHelper : : UNPROTECTED_WEB ) ;
 }
 EXPECT_TRUE ( remover -> is_removing ( ) ) ;
 BlockUntilBrowsingDataRemoved ( base : : Time ( ) , base : : Time : : Max ( ) , BrowsingDataRemover : : REMOVE_COOKIES , BrowsingDataHelper : : UNPROTECTED_WEB ) ;
 EXPECT_FALSE ( remover -> is_removing ( ) ) ;
 }