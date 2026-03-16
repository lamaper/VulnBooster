TEST_F ( BrowsingDataRemoverImplTest , RemoveMultipleTypes ) {
 RemoveDownloadsTester downloads_tester ( GetBrowserContext ( ) ) ;
 EXPECT_CALL ( * downloads_tester . download_manager ( ) , RemoveDownloadsByURLAndTime ( _ , _ , _ ) ) ;
 int removal_mask = BrowsingDataRemover : : REMOVE_DOWNLOADS | BrowsingDataRemover : : REMOVE_COOKIES ;
 BlockUntilBrowsingDataRemoved ( base : : Time ( ) , base : : Time : : Max ( ) , removal_mask , false ) ;
 EXPECT_EQ ( removal_mask , GetRemovalMask ( ) ) ;
 EXPECT_EQ ( BrowsingDataHelper : : UNPROTECTED_WEB , GetOriginTypeMask ( ) ) ;
 StoragePartitionRemovalData removal_data = GetStoragePartitionRemovalData ( ) ;
 EXPECT_EQ ( removal_data . remove_mask , StoragePartition : : REMOVE_DATA_MASK_COOKIES ) ;
 EXPECT_EQ ( removal_data . quota_storage_remove_mask , StoragePartition : : QUOTA_MANAGED_STORAGE_MASK_ALL ) ;
 }