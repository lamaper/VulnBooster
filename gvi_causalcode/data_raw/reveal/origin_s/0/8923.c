static void _setWithOids ( ArchiveHandle * AH , TocEntry * te ) {
 if ( AH -> currWithOids != te -> withOids ) {
 _doSetWithOids ( AH , te -> withOids ) ;
 AH -> currWithOids = te -> withOids ;
 }
 }