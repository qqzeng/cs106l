#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <algorithm>

using std::cout;            using std::endl;
using std::string;          using std::unordered_set;
using std::cout;    using std::ifstream;
using std::cin;      using std::cerr;
using std::stringstream;

string GetLine();
int GetInteger();
void OpenFile(ifstream &myStream);
string ReadFileContent(ifstream &myStream);
unordered_set<string> findWikiLinks(const string& page_html);
void PrintSet(unordered_set<string> wikiLinkSet);
string getValidCharacterOfUrl();

int main() {

    /* TODO: Write code here! */

    /* Note if your file reading isn't working, please follow the
     * steps posted on the front page of the CS106L website. Essentially
     * go to the projects tab on the panel on the left, and in the run
     * section, uncheck the "Run in terminal" box and re-check it. This
     * should fix things.
     */
    bool continued = true;
    while (continued) {
        ifstream myStream;
        string content = ReadFileContent(myStream);
        unordered_set<string> wikiLinkSet = findWikiLinks(content);
        PrintSet(wikiLinkSet);
        cout << "Press 1 to continue another figure simulation, otherwise terminated !" << endl;
        continued = GetInteger() == 1;
    }
    cout << "Byte ..." << endl;
    return 0;
}

/* search all legal wiki link from specified html text, return a unordered set.
* 1. /wiki/PAGENAME
* 2. valid url
*/
unordered_set<string> findWikiLinks(const string& page_html) {
    string wikiLinkPattern = " href=\"/wiki/";
    string quotation = "\"";
    auto start = page_html.begin();
    auto end = page_html.end();
    unordered_set<string> wikiLinkSet;
    string validUrlChar = getValidCharacterOfUrl();
    while(start != end) {
        /* find the start of a underlying wiki hypertext link. */
        auto curr = std::search(start, end, wikiLinkPattern.begin(), wikiLinkPattern.end());
        if(curr == end) break;

        /* find the end of a link. */
        start = curr + wikiLinkPattern.size();
        auto wikiLinkEnd = std::search(start, end, quotation.begin(), quotation.end());
        if(wikiLinkEnd == end) break;

        /* extract the wiki link text. */
        auto wikiLinkStart = curr + string(" href=\"").size();
        cout << string(start, wikiLinkEnd) << endl;
        bool valid = std::all_of(start, wikiLinkEnd,[validUrlChar](char ch) {
            return std::find(validUrlChar.begin(), validUrlChar.end(), ch) != validUrlChar.end();
        });
        /* save the wiki link text if valid. */
        if (valid) {
            wikiLinkSet.insert(string(wikiLinkStart, wikiLinkEnd));
        }
        /* continue. */
        start = wikiLinkEnd + 1;
    }
    return wikiLinkSet;
}

/* All legal character of url.
 * refer: http://www.rfc-editor.org/rfc/rfc1738.txt */
string getValidCharacterOfUrl() {
    string escape  = "%";
    string extra   = "!*'(),";
    string safe    = "$-_.+";
    string digit   = "0123456789";
    string hialpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string lowalpha= "abcdefghijklmnopqrstuvwxyz";
    string alpha   = lowalpha + hialpha;
    string unreserved = alpha + digit + safe + extra;
    string uchar   = unreserved + escape;
    return uchar;
}

/* Print items of set. */
void PrintSet(unordered_set<string> wikiLinkSet) {
    for (unordered_set<string>::const_iterator itr = wikiLinkSet.cbegin();
         itr != wikiLinkSet.cend(); ++itr) {
        cout << *itr << endl;
    }
}

/* Read all content of specified file. */
string ReadFileContent(ifstream &myStream) {
    OpenFile(myStream);
    std::ostringstream tmp;
    tmp << myStream.rdbuf();
    return tmp.str();
}

/* Open a file by given its input file stream and return it if it indeed exists. */
void OpenFile(ifstream &myStream) {
    cout << "Please enter the file name: " << endl;
    string fileName;
    while (true) {
        fileName = GetLine();
        myStream.open(fileName);
        if (!myStream.is_open()) {
            cerr << "Couldn't open the file: " << fileName << endl;
            myStream.clear();
        } else {
            cout << "Open the file successfully!"<< endl;
            return;
        }
    }
}

/* Read a line from standard input. */
string GetLine() {
    string result;
    getline(cin, result);
    return result;
}

/* input a integer value from standard input until user enter a valid value.  */
int GetInteger() {
    while (true) {
        stringstream converter;
        converter << GetLine();
        int result;
        if (converter >> result) {
            char remaining;
            if (converter >> remaining)
                cout << "Unexpected character: " << remaining << endl;
            else
                return result;
        } else
            cout << "Please enter an integer, Retry: " << endl;
    }
}
