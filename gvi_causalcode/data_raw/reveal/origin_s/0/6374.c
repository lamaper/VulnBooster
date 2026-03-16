static void redohead ( struct alltabs * at ) {
 if ( at -> headf ) fclose ( at -> headf ) ;
 at -> headf = tmpfile ( ) ;
 putlong ( at -> headf , at -> head . version ) ;
 putlong ( at -> headf , at -> head . revision ) ;
 putlong ( at -> headf , at -> head . checksumAdj ) ;
 putlong ( at -> headf , at -> head . magicNum ) ;
 putshort ( at -> headf , at -> head . flags ) ;
 putshort ( at -> headf , at -> head . emunits ) ;
 putlong ( at -> headf , at -> head . createtime [ 1 ] ) ;
 putlong ( at -> headf , at -> head . createtime [ 0 ] ) ;
 putlong ( at -> headf , at -> head . modtime [ 1 ] ) ;
 putlong ( at -> headf , at -> head . modtime [ 0 ] ) ;
 putshort ( at -> headf , at -> head . xmin ) ;
 putshort ( at -> headf , at -> head . ymin ) ;
 putshort ( at -> headf , at -> head . xmax ) ;
 putshort ( at -> headf , at -> head . ymax ) ;
 putshort ( at -> headf , at -> head . macstyle ) ;
 putshort ( at -> headf , at -> head . lowestreadable ) ;
 putshort ( at -> headf , at -> head . dirhint ) ;
 putshort ( at -> headf , at -> head . locais32 ) ;
 putshort ( at -> headf , at -> head . glyphformat ) ;
 at -> headlen = ftell ( at -> headf ) ;
 if ( ( at -> headlen & 2 ) != 0 ) putshort ( at -> headf , 0 ) ;
 }