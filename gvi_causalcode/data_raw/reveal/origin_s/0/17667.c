static void _moveBefore ( ArchiveHandle * AH , TocEntry * pos , TocEntry * te ) {
 te -> prev -> next = te -> next ;
 te -> next -> prev = te -> prev ;
 te -> prev = pos -> prev ;
 te -> next = pos ;
 pos -> prev -> next = te ;
 pos -> prev = te ;
 }