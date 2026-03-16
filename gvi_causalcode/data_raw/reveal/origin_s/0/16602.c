TEST_F ( SoundContentSettingObserverTest , UnmutedAudioPlayingDoesNotRecordSiteMuted ) {
 ChangeSoundContentSettingTo ( CONTENT_SETTING_ALLOW ) ;
 SimulateAudioStarting ( ) ;
 EXPECT_FALSE ( RecordedSiteMuted ( ) ) ;
 }