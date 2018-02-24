/*
// ch2ascii version 1.1  -- a utility to remove non-printing / control characters
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
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html
//
// This is a simple ustility to remove non-printing characters from
// files.  It will also convert line ending between Dos/Windows and
// *nix formats.
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

unsigned long int flags = 1024;
ifstream srcdoc;

enum FLAG {Version=1, Help=2, Dos=4, Unix=8, aScii=16, aNsi=32, null=64, one=128, Pipe=256, Tabs=512, All=1024};

void help();
void ShowGPL();
void CoutPut(char *docname);
void CinCoutPut();


int main(int argc, char **argv)
{
  unsigned long int filelength = 0;
  if(argc < 2) {
    cout << "You must supply a file name and/or option parameters,\n";
    cout << "or use the -p flag to accept standard imput.\n";
    cout << "Use \"ch2asc -h\" to for more help. \t (exiting)\n";
    return 1;
  }
  for(int i = 1; i < argc; i++) {
    if(argv[i][0] == '-') {
      int k = strlen(argv[i]);
      for(int j = 1; k > j; j++)
	switch(argv[i][j]) {
	case 'v':
	  flags = (flags | Version);
	  break;
	case 'h':
	  flags = (flags | Help);
	  break;
	case 'd':
	  flags = ((flags | Dos) & (~Unix) & (~All) & (~one));
	  break;
	case 'u':
	  flags = ((flags | Unix) & (~Dos) & (~All) & (~one));
	  break;
	case 's':
	  flags = ((flags | aScii) & (~aNsi));
	  break;
	case 'n':
	  flags = ((flags | aNsi) & (!aScii));
	  break;
	case '0':
	  flags = (flags | null);
	  break;
	case '1':
	  flags = ((flags | one) & (~All) & (~Unix) & (~Dos));
	  break;
	case 'p':
	  flags = (flags | Pipe);
	  break;
	case 't':
	  flags = ((flags | Tabs) & (~All));
	  break;
	case 'a':
	  flags = ((flags | All) & (~Dos) & (~Unix) & (~one) & (~Tabs));
	  break;
	default:
	  cerr << "Parameter -" << argv[i][j] << " not recognized!\n";
	  break;
	}
      if(flags & Version) {
	ShowGPL();
	if(flags & !Help) return 0;
      }
      if(flags & Help) {
	help();
	return 0;
      }
      if(flags & Pipe) {
	CinCoutPut();
	flags = (flags & (!Pipe));
      }
    }
    else CoutPut(argv[i]);
  }
  if(flags & null) cout << '\0';
  return 0;
}


void CoutPut(char *docname)
{
  srcdoc.open(docname);
  if(!srcdoc) {
    cerr << "File " << docname << " not found.\n";
    return;
  }
  srcdoc.peek();
  unsigned char docbuf;
  while(!srcdoc.eof()) {
    docbuf = (char)srcdoc.get();
    if((docbuf < 127) && (docbuf > 31))
      cout << docbuf;
    if( ! (flags & All)) {
      if(docbuf == 10) {
	if(flags & Dos)
	  cout << (char) 13 << docbuf;
	if(flags & Unix)
	  cout << docbuf;
	if(flags & one)
	  cout << ' ';
      }
      if((docbuf == 9) && (flags & Tabs))
	cout << docbuf;
    }
    if((docbuf > 127) && (flags & aNsi))
      cout << docbuf;
  }
  srcdoc.close();
}


void CinCoutPut()
{
  unsigned char docbuf;
  while(!cin.eof()) {
    docbuf = (char)cin.get();
    if((docbuf < 127) && (docbuf > 31))
      cout << docbuf;
    if( ! (flags & All)) {
      if(docbuf == 10) {
	if(flags & Dos)
	  cout << (char) 13 << docbuf;
	if(flags & Unix)
	  cout << docbuf;
	if(flags & one)
	  cout << ' ';
      }
      if((docbuf == 9) && (flags & Tabs))
	cout << docbuf;
    }
    if((docbuf > 127) && (flags & aNsi))
      cout << docbuf;
  }
}


void ShowGPL()
{
  cout << "\n  ch2asc version 1.1, Copyright (C) 2000 Jared Blackburn";
  cout << "\n  ch2asc comes with ABSOLUTELY NO WARRANTY";
  cout << "\n  This is free software, and you are welcome";
  cout << "\n  to redistribute it under certain conditions;";
  cout << "\n  for details see: http://www.gnu.org/copyleft/gpl.html\n\n";
}


void help()
{
  cout << "\nch2asc [-options] file\n";
  cout << "\nWhere \"file\" is a source file containing non-printing\n";
  cout << "charactres When run, ch2asc will output all printing\n";
  cout << "characters to the standard output.  Typically, this would be\n";
  cout << "redirected to for a file, like so: ch2ascii file > newfile\n";
  cout << "\nAlso, these flags, which may be changed between files:\n";
  cout << "\n\t-h\tHelp: Display this help message and exit.\n";
  cout << "\n\t-v\tVersion: Disply version and liscence information\n";
  cout << "\t\tonly, then exit\n";
  cout << "\n\t-d\tDos: Convert UNIX [LF] line breaks to DOS [CR][LF]\n";
  cout << "\t\tline breaks.\n";
  cout << "\n\t-u\tUnix: Convert DOS [CR][LF] line breaks\n";
  cout << "\t\tto UNIX [LF] line breaks.\n";
  cout << "\n\t-s\taScii: (default) Retain only standard ASCII characters,\n";
  cout << "\t\thowing out those with a value greater than 127; this will\n";
  cout << "\t\tremove international\n\t\tand \"wind-ding\" chracters.\n";
  cout << "\n\t-n\taNsi: Use new \"ANSI\" or \"extended ASCII\" character\n";
  cout << "\t\tset.  This retains international and \"wing-ding\" characters\n";
  cout << "\n\t-0\tnull Terminate: add a \"null terminator\" character to the\n";
  cout << "\t\tend of the file, for compatibility with older version of DOS.\n";
  cout << "\n\t-1\tone line: remove all [CR] and [LF] characters, replacing\n";
  cout << "\t\tthen with spaces and making the file one long line.";
  cout << "\n\t-t\tTabs: keep [tab] characters.\n";
  cout << "\n\t-a\tAll: (default) Remove *ALL* control characters, including\n";
  cout << "\t\tline breaks and tabs, and do not replace. (-u -d -t and -1 unset.)\n";
  cout << "\t\tand tabs, and do not replace.  Unsets -u -d -1 and -t, also.\n";
  cout << "\n\t-p\tPipe: Accept standard imput starting after this argument\n";
  cout << "\t\tstring.  Note that only one pipe can be used. If no pipe,\n";
  cout << "\t\tyou type.\n";
  cout << "\nCopyright (C) 2000 Jared Blackburn, enlil@utk.edu\n";
}
