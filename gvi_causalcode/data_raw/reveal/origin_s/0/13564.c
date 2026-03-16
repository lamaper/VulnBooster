TEST_F ( BrowsingDataRemoverImplTest , MultipleTasks ) {
 BrowsingDataRemoverImpl * remover = static_cast < BrowsingDataRemoverImpl * > ( BrowsingDataRemoverFactory : : GetForBrowserContext ( GetBrowserContext ( ) ) ) ;
 EXPECT_FALSE ( remover -> is_removing ( ) ) ;
 std : : unique_ptr < BrowsingDataFilterBuilder > filter_builder_1 ( BrowsingDataFilterBuilder : : Create ( BrowsingDataFilterBuilder : : WHITELIST ) ) ;
 std : : unique_ptr < BrowsingDataFilterBuilder > filter_builder_2 ( BrowsingDataFilterBuilder : : Create ( BrowsingDataFilterBuilder : : BLACKLIST ) ) ;
 filter_builder_2 -> AddRegisterableDomain ( "example.com" ) ;
 MultipleTasksObserver observer ( remover ) ;
 BrowsingDataRemoverCompletionInhibitor completion_inhibitor ;
 std : : list < BrowsingDataRemoverImpl : : RemovalTask > tasks ;
 tasks . emplace_back ( base : : Time ( ) , base : : Time : : Max ( ) , BrowsingDataRemover : : REMOVE_HISTORY , BrowsingDataHelper : : UNPROTECTED_WEB , BrowsingDataFilterBuilder : : Create ( BrowsingDataFilterBuilder : : BLACKLIST ) , observer . target_a ( ) ) ;
 tasks . emplace_back ( base : : Time ( ) , base : : Time : : Max ( ) , BrowsingDataRemover : : REMOVE_COOKIES , BrowsingDataHelper : : PROTECTED_WEB , BrowsingDataFilterBuilder : : Create ( BrowsingDataFilterBuilder : : BLACKLIST ) , nullptr ) ;
 tasks . emplace_back ( base : : Time : : Now ( ) , base : : Time : : Max ( ) , BrowsingDataRemover : : REMOVE_PASSWORDS , BrowsingDataHelper : : ALL , BrowsingDataFilterBuilder : : Create ( BrowsingDataFilterBuilder : : BLACKLIST ) , observer . target_b ( ) ) ;
 tasks . emplace_back ( base : : Time ( ) , base : : Time : : UnixEpoch ( ) , BrowsingDataRemover : : REMOVE_WEBSQL , BrowsingDataHelper : : UNPROTECTED_WEB , std : : move ( filter_builder_1 ) , observer . target_b ( ) ) ;
 tasks . emplace_back ( base : : Time : : UnixEpoch ( ) , base : : Time : : Now ( ) , BrowsingDataRemover : : REMOVE_CHANNEL_IDS , BrowsingDataHelper : : ALL , std : : move ( filter_builder_2 ) , nullptr ) ;
 for ( BrowsingDataRemoverImpl : : RemovalTask & task : tasks ) {
 if ( ! task . observer && task . filter_builder -> IsEmptyBlacklist ( ) ) {
 remover -> Remove ( task . delete_begin , task . delete_end , task . remove_mask , task . origin_type_mask ) ;
 }
 else if ( task . filter_builder -> IsEmptyBlacklist ( ) ) {
 remover -> RemoveAndReply ( task . delete_begin , task . delete_end , task . remove_mask , task . origin_type_mask , task . observer ) ;
 }
 else if ( ! task . observer ) {
 remover -> RemoveWithFilter ( task . delete_begin , task . delete_end , task . remove_mask , task . origin_type_mask , std : : move ( task . filter_builder ) ) ;
 }
 else {
 remover -> RemoveWithFilterAndReply ( task . delete_begin , task . delete_end , task . remove_mask , task . origin_type_mask , std : : move ( task . filter_builder ) , task . observer ) ;
 }
 }
 for ( BrowsingDataRemoverImpl : : RemovalTask & task : tasks ) {
 EXPECT_TRUE ( remover -> is_removing ( ) ) ;
 observer . ClearLastCalledTarget ( ) ;
 completion_inhibitor . BlockUntilNearCompletion ( ) ;
 completion_inhibitor . ContinueToCompletion ( ) ;
 EXPECT_EQ ( task . observer , observer . GetLastCalledTarget ( ) ) ;
 EXPECT_EQ ( task . remove_mask , GetRemovalMask ( ) ) ;
 EXPECT_EQ ( task . origin_type_mask , GetOriginTypeMask ( ) ) ;
 EXPECT_EQ ( task . delete_begin , GetBeginTime ( ) ) ;
 }
 EXPECT_FALSE ( remover -> is_removing ( ) ) ;
 }