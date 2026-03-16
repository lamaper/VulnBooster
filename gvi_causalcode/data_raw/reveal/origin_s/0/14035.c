TEST_F ( HistoryQuickProviderTest , PreventInlineAutocomplete ) {
 std : : vector < std : : string > expected_urls ;
 expected_urls . push_back ( "http://popularsitewithroot.com/" ) ;
 RunTest ( ASCIIToUTF16 ( "popularsitewithr" ) , false , expected_urls , true , ASCIIToUTF16 ( "popularsitewithroot.com" ) , ASCIIToUTF16 ( "oot.com" ) ) ;
 RunTest ( ASCIIToUTF16 ( "popularsitewithr" ) , true , expected_urls , false , ASCIIToUTF16 ( "popularsitewithroot.com" ) , ASCIIToUTF16 ( "oot.com" ) ) ;
 RunTest ( ASCIIToUTF16 ( "popularsitewithroot.com" ) , true , expected_urls , true , ASCIIToUTF16 ( "popularsitewithroot.com" ) , base : : string16 ( ) ) ;
 RunTest ( ASCIIToUTF16 ( "popularsitewithroot.com/" ) , true , expected_urls , true , ASCIIToUTF16 ( "popularsitewithroot.com" ) , base : : string16 ( ) ) ;
 }