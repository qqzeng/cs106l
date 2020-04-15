#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>
#include <fstream>
#include <numeric>
#include <direct.h>
#include <cmath>
#include <map>
#include <set>
#include <time.h>

using namespace std;

/* Program solutions in chapter 7, i.e., STL Algorithms */

/* judge whether a string is palindrome. */
bool IsNotAlpha(char ch) {
    return !isalpha(ch);
}
bool IsPalindrome(string &input) {
    input.erase(remove_if(input.begin(), input.end(), IsNotAlpha), input.end());
    transform(input.begin(), input.end(), input.begin(), ::toupper);
    return equal(input.begin(), input.begin()+input.size()/2, input.rbegin());
}
void TestIsPalindrome() {
    vector<string>  vs = {"Go hang a salami!  I'm a lasagna hog", "Mr. Owl ate my metal worm", "Part y traP", "you are you!"};
    for (size_t i = 0; i < vs.size(); ++i) cout << boolalpha << IsPalindrome(vs[i]) << endl;
}

/* judge whether a string is word-palindrome. */

bool IsNotAlphaAndSpace(char ch) {
    return !isalpha(ch) && ch != ' ';
}
bool IsWordPalindrome(string &input) {
    input.erase(remove_if(input.begin(), input.end(), IsNotAlphaAndSpace), input.end());
    transform(input.begin(), input.end(), input.begin(), ::toupper);
    stringstream text(input);
    vector<string> words;
//    words.insert(words.begin(), istream_iterator<string>(text), istream_iterator<string>());
    copy(istream_iterator<string>(text), istream_iterator<string>(), back_inserter(words));
    return equal(words.begin(), words.begin()+words.size()/2, words.rbegin());
}
void TestIsWordPalindrome() {
    vector<string>  vs = {"Hello?  Hello!?   HELLO?", "Go hang a salami!  I'm a lasagna hog", "Did mom pop?  Mom did!",
                          "Mr. Owl ate my metal worm", "Part y traP", "you are you!"};
    for (size_t i = 0; i < vs.size(); ++i) cout << boolalpha << IsWordPalindrome(vs[i]) << endl;
}

/************************************************ Exercise solutions. ************************************************/

/* Exercise 6. */
bool NotInRange(int num) {
    return num >= 75 || num <= 25;
}
void GetAvgOfRangeOfValuesFromFile(string file_name) {
    fstream input(file_name);
    if (!input.is_open()) {
        cerr << "Open file " << file_name << "fail, abort successive computing...";
        return;
    }
    vector<int> values;
    values.insert(values.begin(), istream_iterator<int>(input), istream_iterator<int>());
    values.erase(remove_if(values.begin(), values.end(), NotInRange), values.end());
    cout << accumulate(values.cbegin(), values.cend(), 0) / values.size() << endl;
    cout << accumulate(values.cbegin(), values.cend(), 0) / distance(values.cbegin(), values.cend()) << endl;
}

void TestGetAvgOfRangeOfValuesFromFile() {
    char *cur_dir;
    if((cur_dir = getcwd(NULL, 0)) == NULL) {
        perror("getcwd error");
    }
    string dir(cur_dir);
    dir = dir.substr(0, dir.find_last_of('\\')+1);
    GetAvgOfRangeOfValuesFromFile(dir + string("exe06_nums.txt"));
}

/* Exercise 7. */
bool isLEThan(string &s) {
    return s.size() <= 3;
}
void RemoveShortWords(vector<string> &strs) {
    strs.erase(remove_if(strs.begin(), strs.end(), isLEThan), strs.end());
    copy(strs.begin(), strs.end(), ostream_iterator<string>(cout, " "));
}
void TestRemoveShortWords() {
    vector<string> strs = {"Today", "is", "a", "nice", "day", "and",
                           "I", "wanna", "to", "play", "with", "my", "good", "friends"};
    RemoveShortWords(strs);
}

/* Exercise 8. */
double DistanceToOrigin(vector<double> &points) {
    return sqrt(inner_product(points.begin(), points.end(), points.begin(), 0.));
}
void TestDistanceToOrigin() {
    vector<double> dv = {2.1, 3, 4};
    cout << DistanceToOrigin(dv) << endl;
}

/* Exercise 9. */
bool StrCompare(string &s1, string &s2) {
    if (strcmp(s1.c_str(), "Me First,") == 0) {
        return true;
    } else if (strcmp(s2.c_str(), "Me First,") == 0) {
        return false;
    } else {
        return s1.compare(s2) < 0; // case-sensitive
    }
}

void BiasedSort(vector<string> &strs) {
    sort(strs.begin(), strs.end(), StrCompare);
    copy(strs.begin(), strs.end(), ostream_iterator<string>(cout, " "));
}

void TestBiasedSort() {
    vector<string> strs = {"Today", "is", "a", "nice", "day", "and", "Me First,",
                           "I", "wanna", "to", "play", "with", "my", "good", "friends", "Me First,"};
    BiasedSort(strs);
}

/* Exercise 10. */
multimap<double, string> InvertMap(map<string, double> &m) {
    multimap<double, string> invert_m;
    for (map<string, double>::iterator itr = m.begin(); itr != m.end(); ++itr) {
        invert_m.insert(make_pair(itr->second, itr->first));
    }
    return invert_m;
}

set<string> TopNSongs(map<string, double> &song_ratings, size_t n) {
    multimap<double, string> invert_m = InvertMap(song_ratings);
    set<string> topn_songs;
    size_t i = 0;
    for (multimap<double, string>::reverse_iterator itr = invert_m.rbegin();
         itr != invert_m.rend() && i++ < n; ++itr) {
        topn_songs.insert(itr->second);
    }
    return topn_songs;
}

void TestTopNSongs() {
    map<string, double> song_ratings;
    song_ratings.insert(make_pair("ac", 8.8));
    song_ratings.insert(make_pair("b", 8.2));
    song_ratings.insert(make_pair("cd", 7.1));
    song_ratings.insert(make_pair("dad", 8.9));
    song_ratings.insert(make_pair("ee", 9.9));
    song_ratings.insert(make_pair("faaa", 9.0));
    song_ratings.insert(make_pair("gbb", 6.0));
    set<string> songs = TopNSongs(song_ratings, 3);
    copy(songs.begin(), songs.end(), ostream_iterator<string>(cout, " "));
}

/* Exercise 11. */
int count(vector<int>::iterator start, vector<int>::iterator stop, int element) {
    size_t total = 0;
    while (start != stop) {
        if (*start == element) total++;
        ++start;
    }
    return total;
}

void TestCount() {
    vector<int> vc = {8, 3, 7, 5, 6, 9, 6, 10, 1, 6, 5, 2};
    cout << count(vc.begin(), vc.end(), 100) << endl;
}

/* Exercise 12. */
double AvgRandomNumber(size_t n) {
    vector<int> values(n);
    srand(static_cast<unsigned int>(time(nullptr)));
    generate_n(values.begin(), n, rand);
    return accumulate(values.begin(), values.end(), 0.0) / values.size();
}

void TestAvgAvgRandomNumber() {
    cout << AvgRandomNumber(3) << endl;
}

/* Exercise 13. */
double MedianEleOfVector(vector<double> &values) {
    nth_element(values.begin(), values.begin() + values.size() / 2, values.end());
    if (values.size() % 2 == 1) {
        return values[values.size() / 2];
    } else {
        return (values[values.size() / 2] + values[values.size() / 2 -1]) / 2;
    }
}

void TestMedianEleOfVector() {
    vector<double > vc = {8, 3, 7, 5, 6.5, 9, 7, 1, 6, 5, 2};
    cout << MedianEleOfVector(vc) << endl;
    sort(vc.begin(), vc.end());
    copy(vc.begin(), vc.end(), ostream_iterator<double>(cout, " "));
}

/* Exercise 14. */
void PrintFileContent(string file_name) {
    fstream file(file_name);
    if (!file.is_open()) {
        cerr << "Error open file " << file_name << endl;
        return;
    }
    copy(istream_iterator<string>(file), istream_iterator<string>(), ostream_iterator<string>(cout, " "));
}

void TestPrintFileContent() {
    char *cur_dir;
    if((cur_dir = getcwd(NULL, 0)) == NULL) {
        perror("getcwd error");
    }
    string dir(cur_dir);
    dir = dir.substr(0, dir.find_last_of('\\')+1);
    PrintFileContent(dir + string("exe06_nums.txt"));
}


/* Exercise 15. */
void OutputToFile(vector<string> &values) {
    ofstream file("test.txt");
    if (!file.is_open()) {
        cerr << "Error open file test.txt" << endl;
        return;
    }
    copy(values.begin(), values.end(), ostream_iterator<string>(file, "\n"));
}

void TestOutputToFile() {
    vector<string> strs = {"Today", "is", "a", "nice", "day", "and", "Me First,",
                           "I", "wanna", "to", "play", "with", "my", "good", "friends", "Me First,"};
    OutputToFile(strs);
}

/* Exercise 16. */
vector<int> IntersectionOfVector(vector<int> &v1, vector<int> &v2) {
    vector<int> result;
//    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_insert_iterator<vector<int>>(result));
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));
    return result;
}

void TestIntersectionOfVector() {
    vector<int> vc1 = {8, 3, 7, 5, 6, 9, 7, 1, 6, 55, 2};
    vector<int> vc2 = {88, 6, 73, 53, 6, 9, 2, 1, 6, 1, 55};
    sort(vc1.begin(), vc1.end());
    sort(vc2.begin(), vc2.end());
    vector<int> result = IntersectionOfVector(vc1, vc2);
    copy(result.begin(), result.end(), ostream_iterator<int>(cout, " "));
}

/* Exercise 17. */
char Encrypt(char c) {

}
string MonoalphabeticSubstitutionEncrypt(string &plain_text) {
    string alphbet = "abcdefghiklmnopqrstuvwxyz";
    string cipher_text = plain_text;
    random_shuffle(alphbet.begin(), alphbet.end());
    for (string::iterator itr = cipher_text.begin(); itr != cipher_text.end(); ++itr) *itr = alphbet[*itr-'a'];
    return cipher_text;
}

void TestMonoalphabeticSubstitutionEncrypt() {
    string plain_text = "todayisaniceday";
    cout << MonoalphabeticSubstitutionEncrypt(plain_text) << endl;
}

int main() {
    TestMonoalphabeticSubstitutionEncrypt();
//    TestIntersectionOfVector();
//    TestOutputToFile();
//    TestPrintFileContent();
//    TestMedianEleOfVector();
//    TestAvgAvgRandomNumber();
//    TestCount();
//    TestTopNSongs();
//    TestBiasedSort();
//    TestDistanceToOrigin();
//    TestRemoveShortWords();
//    TestGetAvgOfRangeOfValuesFromFile();
//    TestIsWordPalindrome();
//    TestIsPalindrome();
    return 0;
}