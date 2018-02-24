/*
// htmlpp -- the html macro preprocessor.
// Copyright (C) 2000 Jared Blackburn.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License version 2.0
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html
//
// This is a simple ustility to act as a macro-prossesor for html
// documents.  Macros are stored as separate files, with the and
// are used by inserting <@filename> into the document.
// Primary source docuemnts are entered on the command line, and
// a macro-expanded version is sent to the standard output.
//
// This program was written by Jared Blackburn, on 11 June 2000,
// and is considerd property and Copyright (C) of the same.
// For questions of comments contact:
//
// Jared Blackburn
//
// For more information about the GNU General Public Liscnece see:
// http://www.gnu.org/copyleft/gpl.html
*/

// Note: Includes updated and namespace added 24 February 2017
// Original includes:
#if 0
#include <iostream.h>
#include <fstream.h>
#include <string.h>
#endif

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

void htmlparse(ifstream &rfile);
void openmacro(ifstream &rfile);
void cinparse();
void ShowGPL();
void help();

// Take the commandline, open the primary source (rootdoc), and
// then pass it to htmlparse() to search for files to insert.
int main(int argc, char **argv)
{
  ifstream rootdoc;
  if(argc < 2) {
    cinparse();
    return 0;
  }
  if(argc > 2) {
    cerr << "Too many parameters -- confused! (Exiting)\n";
    return argc;
  }
  if( ( !strcmp(argv[1],"-v")
     || !strcmp(argv[1],"--version")
     || !strcmp(argv[1],"-gpl")
     || !strcmp(argv[1],"--gpl")
     || !strcmp(argv[1],"-c"))) {
    ShowGPL();
    return 0;
  }
  if( ( !strcmp(argv[1],"-h")
     || !strcmp(argv[1],"-?")
     || !strcmp(argv[1],"--help"))) {
    help();
    return 0;
  }
  rootdoc.open(argv[1]);
  if(!rootdoc) {
    cerr << "Could not find or couldn't open file.";
    return 1;
  }
  cerr << endl;
  htmlparse(rootdoc);
  if(rootdoc.get() != '\n') cout << endl;
  cerr << endl;
  return 0;
}


// This searches through a source document for files to expand, and,
// when it finds one, passes it to openmacro() which reads the file
// name and opens it.  This function is designed to read ahead before
// re-outputing, so that the comment encapsulating the macro file may
// be thown out.
void htmlparse(ifstream &rfile)
{
  char htmlbuf[3];
  htmlbuf[2] = '\0';
  htmlbuf[1] = htmlbuf[0] = rfile.peek();
  rfile.get(htmlbuf[1]);
  while(!rfile.eof()) {
    htmlbuf[0] = htmlbuf[1];
    rfile.get(htmlbuf[1]);
    if(!strcmp(htmlbuf,"<@")) {
      openmacro(rfile);
      if(rfile.eof()) return;
      else rfile.get(htmlbuf[1]);
    }
    else cout << htmlbuf[0];
  }
  cout << htmlbuf[1];
}


// This acts just lile htmlparse() and openmacro(), but reads from
// common imput
void cinparse()
{
  char htmlbuf[3];
  htmlbuf[2] = '\0';
  htmlbuf[1] = htmlbuf[0] = cin.peek();
  cin.get(htmlbuf[1]);
  while(!cin.eof()) {
    htmlbuf[0] = htmlbuf[1];
    cin.get(htmlbuf[1]);
    if(!strcmp(htmlbuf,"<@")) {
      {
	ifstream macro;
	char macrofile[128];
	char htmlbuf;
	int i = 0;
	do {
	  if(cin.eof()) break;
	  cin.get(htmlbuf);
	  macrofile[i++] = htmlbuf;
	} while((htmlbuf != '>') && (!cin.eof()));
	macrofile[--i] = '\0';
	macro.open(macrofile);
	if(!macro) {
	  cerr << "Macro file " << macrofile << " not found!\n";
	}
	if((macro.peek()) && (!macro.eof())) htmlparse(macro);
	macro.close();
      }
      if(cin.eof()) return;
      else cin.get(htmlbuf[1]);
    }
    else cout << htmlbuf[0];
  }
  cout << htmlbuf[1];
}


// This reads a macrofiles name out of a source file, then opens that macro
// file.  Control is then passes back to htmlparse() to actually read and
// output the macro contents.  Note that this recursion make it possible for
// inserted files to have their own insertions, and so on, as long as two files
// do not try to insert each other (which would create an infinite loop). Note
// also the all passing is done by refference, so the ifstreams will not loose
// there place in files being read.
void openmacro(ifstream &rfile)
{
  ifstream macro;
  char macrofile[128];
  char htmlbuf;
  int i = 0;
  do {
    if(rfile.eof()) break;
    rfile.get(htmlbuf);
    macrofile[i++] = htmlbuf;
  } while((htmlbuf != '>') && (!rfile.eof()));
  macrofile[--i] = '\0';
  macro.open(macrofile);
  if(!macro)
    cerr << "Macro file " << macrofile << " not found!\n";
  else if((macro.peek()) && (!macro.eof())) htmlparse(macro);
  macro.close();
}


void ShowGPL()
{
  cout << "\n  htmlpp version 1.2, Copyright (C) 2000 Jared Blackburn";
  cout << "\n  htmlpp comes with ABSOLUTELY NO WARRANTY";
  cout << "\n  This is free software, and you are welcome";
  cout << "\n  to redistribute it under certain conditions;";
  cout << "\n  for details see: http://www.gnu.org/copyleft/gpl.html\n\n";
}


void help()
{
  ShowGPL();
  cout << "\nhtmlpp file | -options\n";
  cout << "\nWhere \"file\" is a source file, usually html, for which other file";
  cout << "\nnames are embedded in it text, in this form <@macroname>  where";
  cout << "\n\"macroname\" is the name of a file that contains text to be inserted.";
  cout << "\nWhen run, htmlpp should output to the contents of [file] to the";
  cout << "\nstandard output, while replacing text in the from <@macrofile> with";
  cout << "\nthe contents of [macrofile].  Usually, the out put would be redirect to";
  cout << "\ncreate a new file, like so:  htmlpp file > newfile.";
  cout << "\nIf no file is name, data will be read from the standard imput.\n";
  cout << "\nAlso:";
  cout << "\n\t-h\n\t-?\n\t--help\t\tDisplay this help message and exit.\n";
  cout << "\n\t-v\n\t-c\n\t-gpl\n\t--gpl\n\t--version\tDisply version and liscence information only, then exit.\n";
  cout << "\nCopyright (C) 2000 Jared Blackburn, enlil@utk.edu\n";
}
