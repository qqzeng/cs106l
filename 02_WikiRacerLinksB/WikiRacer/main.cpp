#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>
#include <unordered_map>
#include "wikiscraper.h"


using std::cout;            using std::endl;
using std::string;          using std::vector;
using std::priority_queue;  using std::unordered_map;
using std::unordered_set;


/*
 * This is the function you will be implementing. It takes
 * two string representing the names of a start_page and
 * end_page and is supposed to return a ladder, represented
 * as a vector<string>, of links that can be followed from
 * start_page to get to the end_page.
 *
 * For the purposes of this algorithm, the "name" of a Wikipedia
 * page is what shows at the end of the URL when you visit that page
 * in your web browser. For ex. the name of the Stanford University
 * Wikipedia page is "Stanford_University" since the URL that shows
 * in your browser when you visit this page is:
 *
 *       https://en.wikipedia.org/wiki/Stanford_University
 */
vector<string> findWikiLadder(const string& start_page, const string& end_page) {
    WikiScraper scraper;
    /* comparator of priority queue for comparing two ladders. */
    auto cmpFn = [end_page, &scraper](const vector<string>& ladder1, const vector<string>& ladder2) -> bool{
        const string endPage1 = ladder1.back();
        const string endPage2 = ladder2.back();
        const unordered_set<string> linkSet = scraper.getLinkSet(end_page);
        const unordered_set<string> linkSet1 = scraper.getLinkSet(endPage1);
        const unordered_set<string> linkSet2 = scraper.getLinkSet(endPage2);
//        unsigned sharedLinkNum1 = 0;
//        unsigned sharedLinkNum2 = 0;
//        for (string link : linkSet) {
//          if (linkSet1.count(link) > 0) {
//            ++sharedLinkNum1;
//          }
//          if (linkSet2.count(link) > 0) {
//            ++sharedLinkNum2;
//          }
//        }
//        return sharedLinkNum1 < sharedLinkNum2;
        unordered_set<string> ans1;
        unordered_set<string> ans2;
        std::copy_if(linkSet1.begin(), linkSet1.end(), std::inserter(ans1, ans1.begin()),
                     [&linkSet](const string& ele){return linkSet.count(ele) > 0;});
        std::copy_if(linkSet2.begin(), linkSet2.end(), std::inserter(ans2, ans2.begin()),
                     [&linkSet](const string& ele){return linkSet.count(ele) > 0;});
        return ans1.size() < ans2.size();
    };
    /* the priority queue of ladders. */
    std::priority_queue<vector<string>, vector<vector<string>>,
                            decltype(cmpFn)> ladderQueue(cmpFn);
    unordered_set<string> visited;
    visited.insert(start_page);
    ladderQueue.push({start_page});
    while (!ladderQueue.empty()) {
        vector<string> partialLadder = ladderQueue.top();
        ladderQueue.pop();
        const string wikiName = partialLadder.back();
        visited.insert(wikiName);
        /* Print the wikiName so to understand what it is exporing. */
        cout << wikiName << endl;
        const unordered_set<string> linkSet = scraper.getLinkSet(wikiName);
        if (linkSet.count(end_page) > 0) {
            partialLadder.push_back(end_page);
            return partialLadder;
        }
        for (string neiLink : linkSet) {
            if (visited.find(neiLink) == visited.end()) continue;
            vector<string> newParitalLadder(partialLadder);
            newParitalLadder.push_back(neiLink);
            ladderQueue.push(newParitalLadder);
        }
    }
    return {};
}

int main() {
//    auto ladder = findWikiLadder("Fruit", "Strawberry");
    auto ladder = findWikiLadder("Milkshake", "Gene");
    cout << endl;

    if(ladder.empty()) {
        cout << "No ladder found!" << endl;
    } else {
        cout << "Ladder found:" << endl;
        cout << "\t";

        // Print the ladder here!
    }

    return 0;
}




