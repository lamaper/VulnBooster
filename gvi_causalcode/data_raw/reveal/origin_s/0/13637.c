TEST_F ( SoundContentSettingObserverTest , MutedAudioBlockedBySiteException ) {
 ChangeSoundContentSettingTo ( CONTENT_SETTING_BLOCK ) ;
 SimulateAudioStarting ( ) ;
 EXPECT_TRUE ( RecordedSiteMuted ( ) ) ;
 ExpectRecordedForReason ( SoundContentSettingObserver : : MuteReason : : kSiteException ) ;
 }