TEST_F ( SoundContentSettingObserverTest , MutingAudioWhileSoundIsPlayingBlocksSound ) {
 SimulateAudioPlaying ( ) ;
 EXPECT_FALSE ( RecordedSiteMuted ( ) ) ;
 ChangeSoundContentSettingTo ( CONTENT_SETTING_BLOCK ) ;
 EXPECT_TRUE ( RecordedSiteMuted ( ) ) ;
 ExpectRecordedForReason ( SoundContentSettingObserver : : MuteReason : : kSiteException ) ;
 }