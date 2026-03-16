IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , UseCounterUkmMixedContentFeaturesLogged ) {
 net : : EmbeddedTestServer https_server ( net : : EmbeddedTestServer : : TYPE_HTTPS ) ;
 https_server . AddDefaultHandlers ( base : : FilePath ( FILE_PATH_LITERAL ( "chrome/test/data" ) ) ) ;
 ASSERT_TRUE ( https_server . Start ( ) ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : LOAD_EVENT ) ;
 GURL url = https_server . GetURL ( "/page_load_metrics/use_counter_features.html" ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , url ) ;
 waiter -> Wait ( ) ;
 NavigateToUntrackedUrl ( ) ;
 const auto & entries = test_ukm_recorder_ -> GetEntriesByName ( internal : : kUkmUseCounterEventName ) ;
 EXPECT_EQ ( 6u , entries . size ( ) ) ;
 std : : vector < int64_t > ukm_features ;
 for ( const auto * entry : entries ) {
 test_ukm_recorder_ -> ExpectEntrySourceHasUrl ( entry , url ) ;
 const auto * metric = test_ukm_recorder_ -> GetEntryMetric ( entry , internal : : kUkmUseCounterFeature ) ;
 EXPECT_TRUE ( metric ) ;
 ukm_features . push_back ( * metric ) ;
 }
 EXPECT_THAT ( ukm_features , UnorderedElementsAre ( static_cast < int64_t > ( WebFeature : : kNavigatorVibrate ) , static_cast < int64_t > ( WebFeature : : kDataUriHasOctothorpe ) , static_cast < int64_t > ( WebFeature : : kApplicationCacheManifestSelectSecureOrigin ) , static_cast < int64_t > ( WebFeature : : kMixedContentImage ) , static_cast < int64_t > ( WebFeature : : kMixedContentAudio ) , static_cast < int64_t > ( WebFeature : : kMixedContentVideo ) ) ) ;
 }