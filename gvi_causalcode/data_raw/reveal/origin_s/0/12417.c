static OutputContext SaveOutput ( ArchiveHandle * AH ) {
 OutputContext sav ;
 sav . OF = AH -> OF ;
 sav . gzOut = AH -> gzOut ;
 return sav ;
 }