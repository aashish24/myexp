
#ifndef _TEXT_DISPLAY_H_
#define _TEXT_DISPLAY_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class str {
  public:
  char row[255];
  };
  

class TextDisplay
{
  public:
    TextDisplay()
    {
      const char *files[] = 
      { 
        ".//../data/razdan/Wells/COMMERCIAL.txt",
        ".//../data/razdan/Wells/DRAINAGE.txt",
        ".//../data/razdan/Wells/IRRIGATION.txt",
        ".//../data/razdan/Wells/MUNICIPAL.txt",  
        ".//../data/razdan/Wells/RECHARGE.txt",
        ".//../data/razdan/Wells/STOCK.txt",
        ".//../data/razdan/Wells/UTILITY.txt",
        ".//../data/razdan/Wells/DOMESTIC.txt",
        ".//../data/razdan/Wells/INDUSTRIAL.txt",
        ".//../data/razdan/Wells/MONITORING.txt",
        ".//../data/razdan/Wells/NONE.txt",
        ".//../data/razdan/Wells/RECREATION.txt",
        ".//../data/razdan/Wells/SUBDIVISION.txt",
      };

      std::cerr << " [TextDisplay] Initialization: " << std::endl;
      OpenReadWellFiles(files[0], &comm);      
      OpenReadWellFiles(files[2], &irr);
      OpenReadWellFiles(files[3], &muni);
      OpenReadWellFiles(files[4], &recharge);
      OpenReadWellFiles(files[5], &stock);
      OpenReadWellFiles(files[6], &uti);
      OpenReadWellFiles(files[7], &dom);
      OpenReadWellFiles(files[8], &ind);
      OpenReadWellFiles(files[10], &none);
      OpenReadWellFiles(files[11], &rec);      
    }

    ~TextDisplay(){;}

    void OpenReadWellFiles(const char *,  std::vector<str *>* );
    
    void DisplayWellData (int n, char *tk, char typej);
  
    //char tblock[1024];    
  
    std::vector<str *>  comm;    
    std::vector<str *>  irr;
    std::vector<str *>  muni;
    std::vector<str *>  recharge;
    std::vector<str *>  stock;
    std::vector<str *>  uti;
    std::vector<str *>  dom;
    std::vector<str *>  ind;
  //  std::vector<str *>  mon;
    std::vector<str *>  none;
    std::vector<str *>  rec;
  //  std::vector<str *>  sub;
  
    //cout << "Reading Files now" << endl;
    //cout << "Displaying File data" << endl;
    //DisplayWellData(5, head, tblock, irr);


};

inline void TextDisplay::OpenReadWellFiles(const char *fname, std::vector<str *> *strObj)

{
  cout << "Reading File " << fname << endl;
  
  std::ifstream infile(fname);
    
  while(!infile.eof()) {
  
    str *wstr = new str;
    infile.getline(wstr->row, 255);
    cout << wstr->row << endl;
    strObj->push_back(wstr);
  }
  infile.close();

}


inline void TextDisplay::DisplayWellData (int n, char *tblock, char type )
{
  const char *head[] = { "Well#", "Well ID", "h3", "h4", "h5", "h6", "h7", "Type"};

  // We want to display n-1th entry in tblock  
  std::vector< str *> strobj;  

  switch(type)
  {
    case 'I': {   strobj = irr; break;}
    case 'C': {   strobj = comm; break;}
    case 'D': {   strobj = dom; break;}
    case 'N': {   strobj = none; break;}
    case 'U': {   strobj = uti; break;}
    case 'S': {   strobj = stock; break;}
    case 'R': {   strobj = recharge; break;}
    case 'P': {   strobj = ind; break;}    //: Industrial.    
    case 'A': {   strobj = rec; break;}    //: Rec. 
    case 'B': {   strobj = muni; break;}    //: Muni.     
  }

  memset(tblock, '\0', 1024);

  // cout << " Size is : " << strobj.size() << std::endl;

  if(n >  (int)strobj.size())
  {
    return; 
  }

  char *row = strobj[n-1]->row;
  char *rn;
  
   // cout << "Row is " << row << endl;
  
  strcpy(tblock, head[0]);
  strcat(tblock, "\t");
  rn = strchr(row, ' ');
  *rn = '\0';
  rn++;
  strcat(tblock, row);
  strcat(tblock, "\n");
  
  strcat(tblock, head[1]);
  strcat(tblock, "\t");
  row = rn;
  rn = strchr(rn, ' ');
  *rn = '\0';
  rn++;
  strcat(tblock, row);
  strcat(tblock, "\n");

  strcat(tblock, head[2]);
  strcat(tblock, "\t");
  row = rn;
  rn = strchr(rn, ' ');
  *rn = '\0';
  rn++;
  strcat(tblock, row);
  strcat(tblock, "\n");

  strcat(tblock, head[3]);
  strcat(tblock, "\t");
  row = rn;
  rn = strchr(rn, ' ');
  *rn = '\0';
  rn++;
  strcat(tblock, row);
  strcat(tblock, "\n");

  strcat(tblock, head[4]);
  strcat(tblock, "\t");
  row = rn;
  rn = strchr(rn, ' ');
  *rn = '\0';
  rn++;
  strcat(tblock, row);
  strcat(tblock, "\n");

  strcat(tblock, head[5]);
  strcat(tblock, "\t");
  row = rn;
  rn = strchr(rn, ' ');
  *rn = '\0';
  rn++;
  strcat(tblock, row);
  strcat(tblock, "\n");

  strcat(tblock, head[6]);
  strcat(tblock, "\t");
  row = rn;
  rn = strchr(rn, ' ');
  *rn = '\0';
  rn++;
  strcat(tblock, row);
  strcat(tblock, "\n");

  strcat(tblock, head[7]);
  strcat(tblock, "\t");
  row = rn;
  strcat(tblock, row);
  strcat(tblock, "\n");

  cout <<"Str is " << endl << tblock << endl;
}


#endif //: 


