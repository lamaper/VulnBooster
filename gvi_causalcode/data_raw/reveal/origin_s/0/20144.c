static void dumpghstruct ( struct glyphinfo * gi , struct glyphhead * gh ) {
 putshort ( gi -> glyphs , gh -> numContours ) ;
 putshort ( gi -> glyphs , gh -> xmin ) ;
 putshort ( gi -> glyphs , gh -> ymin ) ;
 putshort ( gi -> glyphs , gh -> xmax ) ;
 putshort ( gi -> glyphs , gh -> ymax ) ;
 if ( gh -> xmin < gi -> xmin ) gi -> xmin = gh -> xmin ;
 if ( gh -> ymin < gi -> ymin ) gi -> ymin = gh -> ymin ;
 if ( gh -> xmax > gi -> xmax ) gi -> xmax = gh -> xmax ;
 if ( gh -> ymax > gi -> ymax ) gi -> ymax = gh -> ymax ;
 }