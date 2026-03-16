TEST_F ( BrowsingDataRemoverImplTest , RemoveQuotaManagedDataForLastHour ) {
 BlockUntilBrowsingDataRemoved ( AnHourAgo ( ) , base : : Time : : Max ( ) , BrowsingDataRemover : : REMOVE_FILE_SYSTEMS | BrowsingDataRemover : : REMOVE_WEBSQL | BrowsingDataRemover : : REMOVE_APPCACHE | BrowsingDataRemover : : REMOVE_SERVICE_WORKERS | BrowsingDataRemover : : REMOVE_CACHE_STORAGE | BrowsingDataRemover : : REMOVE_INDEXEDDB , false ) ;
 EXPECT_EQ ( BrowsingDataRemover : : REMOVE_FILE_SYSTEMS | BrowsingDataRemover : : REMOVE_WEBSQL | BrowsingDataRemover : : REMOVE_APPCACHE | BrowsingDataRemover : : REMOVE_SERVICE_WORKERS | BrowsingDataRemover : : REMOVE_CACHE_STORAGE | BrowsingDataRemover : : REMOVE_INDEXEDDB , GetRemovalMask ( ) ) ;
 EXPECT_EQ ( BrowsingDataHelper : : UNPROTECTED_WEB , GetOriginTypeMask ( ) ) ;
 StoragePartitionRemovalData removal_data = GetStoragePartitionRemovalData ( ) ;
 EXPECT_EQ ( removal_data . remove_mask , StoragePartition : : REMOVE_DATA_MASK_FILE_SYSTEMS | StoragePartition : : REMOVE_DATA_MASK_WEBSQL | StoragePartition : : REMOVE_DATA_MASK_APPCACHE | StoragePartition : : REMOVE_DATA_MASK_SERVICE_WORKERS | StoragePartition : : REMOVE_DATA_MASK_CACHE_STORAGE | StoragePartition : : REMOVE_DATA_MASK_INDEXEDDB ) ;
 uint32_t expected_quota_mask = ~ StoragePartition : : QUOTA_MANAGED_STORAGE_MASK_PERSISTENT ;
 EXPECT_EQ ( removal_data . quota_storage_remove_mask , expected_quota_mask ) ;
 EXPECT_EQ ( removal_data . remove_begin , GetBeginTime ( ) ) ;
 }