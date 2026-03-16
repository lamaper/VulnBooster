static void _uhash_internalSetResizePolicy ( UHashtable * hash , enum UHashResizePolicy policy ) {
 U_ASSERT ( hash != NULL ) ;
 U_ASSERT ( ( ( int32_t ) policy ) >= 0 ) ;
 U_ASSERT ( ( ( int32_t ) policy ) < 3 ) ;
 hash -> lowWaterRatio = RESIZE_POLICY_RATIO_TABLE [ policy * 2 ] ;
 hash -> highWaterRatio = RESIZE_POLICY_RATIO_TABLE [ policy * 2 + 1 ] ;
 }