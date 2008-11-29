<!-- Script to Pull focused ads

	function MM_jumpMenu(targ,selObj,restore){ //v3.0
	  eval(targ+".location='"+selObj.options[selObj.selectedIndex].value+"'");
 	  if (restore) selObj.selectedIndex=0;
	}

   //pull all Gama cookies
   var allcookies = document.cookie;
   //document.write(window.location.pathname);
   //get the current url path
   var current_window = window.location.href;
   //var current_window = window.location;
   
   //Find the position of the Wirereport popup string in the cookie
	//var pos = allcookies.indexOf("wireless=");
	
	//if it isn't there pop it up
	//if (pos == -1) 	window.open('http://www.gamasutra.com/popup.htm','wireless','width=400,height=335');

   //Find the position of the Gama Demographic string in the cookie
   var pos = allcookies.indexOf("GamaDemo200406=");
	
  //generate the date
  var D = new Date();
  
  //pull the browser version
  var bName = navigator.appName;
  
  //some time numbers required for netgravity
  seed = (D.getSeconds() * 0xFFFFFF) + (D.getMinutes() * 0xFFFF); 
  timenum = D.getTime();  
  rand = Math.floor(Math.random()*1);
  //declare variable for ad tag
  var gama_pos = "home";
	
if (current_window.indexOf("article_display.php") != -1) gama_pos = "features";
if (current_window.indexOf("news_index") != -1) gama_pos = "features";

  // if the Gama Demo string exists go for it!
	if (pos != -1) {

		//start of the Gama Demo string	
		var start = pos + 15;
		//end of the Gama Demo string
		var end = allcookies.indexOf(";",start);
		//if the end of the Gama Demo string is the end of the string, set it 	
		if (end == -1) end = allcookies.length;
		//isolate the Gama Demo String
		var value = allcookies.substring(start,end);
		
		//split the Gama Demo String into an array
		value = value.split("|");
		
		//push the different demographics into variables
		var job = value[0];
		var country = value[1];
		var company = value[2];
		var product = value[3];
		var state = value[9];
		//set the ad tag according to what demo graphic information they fall under
		// the further down the tag is set, the higher the precedence it is given
		
		//For microsoft
		//residing in United Kingdom
		//if (country == "United Kingdom") gama_pos = "microsoft";
		//residing in U.S.
		//if (country == "United States") gama_pos = "USA";
		//residing in United Kingdom
		//if (country == "United Kingdom") gama_pos = "UK";
		//residing in Canada
		//if (country == "Canada") gama_pos = "Canada";
		//working in game development company
		//if (company.search(/01|02|03/) != -1) gama_pos = "GameDevelopmentCompany";
		//involved in buying workstations
		//if (product.search(/02/) != -1) gama_pos = "Workstation";
		
		//artists
		//if ((job >= 01) && (job <= 07)) gama_pos = "artists";
		
		//programmers
		//if ((job >= 8) && (job <= 17)) gama_pos = "programmers";
		
		//designers
		//if ((job >= 18) && (job <= 23)) gama_pos = "GameDesigner";
		
		//audio
		//if ((job >= 24) && (job <= 27)) gama_pos = "Audio";
		
		//production
		//if ((job >= 28) && (job <= 38)) gama_pos = "Production";
		
		//business/legal
		//if ((job >= 39) && (job <= 45)) gama_pos = "BizLegal";
		
		//publishing
		//if ((job >= 46) && (job <= 48)) gama_pos = "Publishing";
		
		//multiplayer
		//if ((job >= 46) && (job <= 48)) gama_pos = "multiplayer";
		
		//physics
		//if ((job >= 46) && (job <= 48)) gama_pos = "physics";
		
		
		//programmers, designers and biz folks (for Adventureland)
		//if  (((job >= 8) && (job <= 17)) || ((job >= 18) && (job <= 23)) || ((job >= 39) && (job <= 45))) gama_pos = "progdesignbiz";
		
		
/*
artists		
education
features
home
mobile
multiplayer
physics
programmers
student
UK
USA
*/

		//residing in Europe
		//if (country.search(/Germany|France|Spain|Italy|Denmark|Norway|Finland|Belgium|Switzerland|Ireland|Sweden|United Kingdom/) != -1) gama_pos = "Europe";
	
	
	//Executives for NXN
		if ((job == 02) || (job == 18) || (job == 28) ||  (job == 29) || (job == 30)  || (job == 31) || (job == 46) || (job == 48)) gama_pos = "executives";
		
	//GDC Education Ad Code	
	if (current_window.indexOf("gdc2003/") != -1) gama_pos = "gdc2003";
	
	//Contractor Ad Code	
	if (current_window.indexOf("contract") != -1 || current_window.indexOf("/gig") != -1) gama_pos = "contractor";
	
	//Education homepage and Student Galleries Ad Code	
	if (current_window.indexOf("/education") != -1 || current_window.indexOf("/galleries/student") != -1 || current_window.indexOf("companies.php3?cat=153138") != -1) gama_pos = "education";

//Programmers Ad code for Intel 01/07/2004
	if (current_window.indexOf("article_display.php?category=7") != -1) gama_pos = "programmers";
		http://www.gamasutra.com/php-bin/news_index.php
//Jobs Ad Code	
	if (current_window.indexOf("job") != -1 || current_window.indexOf("resume") != -1 ) gama_pos = "jobs";

	//residing in California, Nevada and page is not contractor.
	//***NOTE: THIS 'IF' STATEMENT SCREWS UP OTHER TARGETED ADS, E.G., FOR THE EDUCATION PAGE -ALEX ***
	//if (state == "ca" || state == "CA" || state == "Ca" || state == "nv" || state == "NV" || state == "Nv" ) {
    //       if (current_window.indexOf("contract") == -1)
    //         gama_pos = "rfx";
	//}	
	
	if (current_window.indexOf("article_display.php")!= -1) gama_pos = "features";
	//Programmers Ad code for Intel 01/07/2004
	if (current_window.indexOf("news_index") != -1) gama_pos = "features";
	//Programmers Ad code for Intel 01/07/2004
	if (current_window.indexOf("features") != -1) gama_pos = "articlesky";

	//beginning of Europe Ad tag
		//if (country.search(/United Kingdom|England|Ireland|Scotland|Wales|Germany|France|Spain|Italy|Netherlands|Austria|Greece|Portugal|Denmark|Norway|Finland|Belgium|Switzerland|Ireland|Sweden/) != -1) gama_pos = "home&country=europe";
			
	//if (current_window.indexOf("article_display.php") && country.search(/United Kingdom|England|Ireland|Scotland|Wales|Germany|France|Netherlands|Austria|Greece|Portugal|Spain|Italy|Denmark|Norway|Finland|Belgium|Switzerland|Ireland|Sweden/) != -1) gama_pos = "features&country=europe";
	
		//if (current_window.indexOf("news_index.php") && country.search(/United Kingdom|England|Ireland|Scotland|Wales|Germany|France|Austria|Greece|Portugal|Netherlands|Spain|Italy|Denmark|Norway|Finland|Belgium|Switzerland|Ireland|Sweden/) != -1) gama_pos = "features&country=europe";
}
//show nxn alienbrain ad on news items that ran during gdc
	if (current_window.indexOf("news_index.php?story=") != -1) {
	var news_pos = current_window.indexOf("story=");
	news_pos = news_pos + 6;
	var news_id = current_window.substring(news_pos); 
	//document.write(news_id);
	news_id = parseInt(news_id);
	if (news_id <= 3629 && news_id >= 3581)	gama_pos = "gdc2004coverage";
	
	
}

	var axel = Math.random();
    var num = axel * 100000000000000000 + "?";

NS4 = document.layers
;if (NS4) {origWidth = innerWidth;origHeight = innerHeight;}
function reDo() {if (innerWidth != origWidth || innerHeight != origHeight) location.reload();}

//if (120x60-C.gif
if (NS4) onresize = reDo;
		
	//write the ad tags to call the ads
	document.write('<IFRAME SRC="http://as.cmpnet.com/html.ng/site=game&affiliate=gamasutra&pagepos=top&gam_pos=' + gama_pos + '&ord='+ num +'"  width="468" height="60" frameborder="no" border="0" marginwidth="0" marginheight="0" SCROLLING="no">');
document.write('<SCRIPT LANGUAGE="Javascript1.1" SRC="http://as.cmpnet.com/js.ng/Params.richmedia=yes&site=game&affiliate=gamasutra&pagepos=top&gam_pos=' + gama_pos + '&ord='+ num +'"><\/SCRIPT>');
  
	 document.write("</IFRAME>");		
	 //testing the tag
	 //if (gama_pos == "gdc2003") document.write(gama_pos);	
	//if (gama_pos == "education") document.write( current_window);	
	//if (gama_pos == "education") document.write( current_window);	
	//document.write(gama_pos);
    document.write("&nbsp; &nbsp;");	
    document.write('<IFRAME SRC="http://as.cmpnet.com/html.ng/site=game&affiliate=gamasutra&pagepos=button&gam_pos=' + gama_pos + '&ord='+ num +'"  width="120" height="60" frameborder="no" border="0" marginwidth="0" marginheight="0" SCROLLING="no">'); 
document.write('<SCRIPT LANGUAGE="Javascript1.1" SRC="http://as.cmpnet.com/js.ng/Params.richmedia=yes&site=game&affiliate=gamasutra&pagepos=button&gam_pos=' + gama_pos + '&ord='+ num +'"><\/SCRIPT>');     
document.write('</IFRAME>');    

//-->
