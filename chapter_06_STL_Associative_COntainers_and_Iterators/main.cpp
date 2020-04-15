#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;
/**
 *  Exercises solutions in chapter 06, i.e., STL Associative Containers and Iterators.
 */

/*********************************** Deterministic Finite Automata ***********************************/
/* the struct of Deterministic Finite Automata. */
struct DFA {
    /* starting state of DFA. */
    int start_state;
    /* state transitions sets: <state, conditional label>, state. */
    map<pair<int, char>, int> transitions;
    /* final accepting states. */
    set<int> accept_states;
    /* trapped states */
    set<int> trapped_states;
};

/* initialize DFA. */
/* an easy example to expound DFA. */
bool ConstructDFA(DFA &dfa) {
    dfa.transitions[make_pair(0, '0')] = 1;
    dfa.transitions[make_pair(0, '1')] = 2;
    dfa.transitions[make_pair(1, '0')] = 1;
    dfa.transitions[make_pair(1, '1')] = 3;
    dfa.transitions[make_pair(2, '1')] = 2;
    dfa.transitions[make_pair(2, '0')] = 3;
    dfa.transitions[make_pair(3, '0')] = 3;
    dfa.transitions[make_pair(3, '1')] = 3;

    dfa.start_state = 0;
    dfa.accept_states.insert(3);
    return true;
}

/* judge whether a specified a string input to be accepted or not. */
bool SimulateDFA(DFA &dfa, string input) {
    int cur_state = dfa.start_state;
    for (string::iterator itr = input.begin(); itr != input.end(); ++itr) {
        cur_state = dfa.transitions[make_pair(cur_state, *itr)];
        if (!dfa.trapped_states.empty()) {
            if (dfa.trapped_states.find(cur_state) != dfa.trapped_states.end()) return false;
        }
    }
    return dfa.accept_states.find(cur_state) != dfa.accept_states.end();
}

void TestDFA1() {
    DFA dfa;
    ConstructDFA(dfa);
    vector<string> strs = {"0011", "001111010101", "0101", "0000"};
    for (vector<string>::iterator itr = strs.begin(); itr != strs.end(); ++itr)
        cout << *itr << (SimulateDFA(dfa, *itr) ? " be accepted!" : " not be accepted!") << endl;
}

/* an email checking example to further expound the application of DFA. */
bool ConstructEmailDFA(DFA &dfa) {
    dfa.transitions[make_pair(0, 'a')] = 1;
    dfa.transitions[make_pair(0, '.')] = 7;
    dfa.transitions[make_pair(0, '@')] = 7;
    dfa.transitions[make_pair(1, 'a')] = 1;
    dfa.transitions[make_pair(1, '.')] = 2;
    dfa.transitions[make_pair(1, '@')] = 3;
    dfa.transitions[make_pair(2, 'a')] = 1;
    dfa.transitions[make_pair(2, '.')] = 7;
    dfa.transitions[make_pair(2, '@')] = 7;
    dfa.transitions[make_pair(3, '.')] = 7;
    dfa.transitions[make_pair(3, '@')] = 7;
    dfa.transitions[make_pair(3, 'a')] = 4;
    dfa.transitions[make_pair(4, 'a')] = 4;
    dfa.transitions[make_pair(4, '.')] = 5;
    dfa.transitions[make_pair(4, '@')] = 7;
    dfa.transitions[make_pair(5, 'a')] = 6;
    dfa.transitions[make_pair(5, '.')] = 7;
    dfa.transitions[make_pair(5, '@')] = 7;
    dfa.transitions[make_pair(6, 'a')] = 6;
    dfa.transitions[make_pair(6, '.')] = 5;
    dfa.transitions[make_pair(6, '@')] = 7;

    dfa.start_state = 0;
    dfa.accept_states.insert(6);
    dfa.trapped_states.insert(7);
    return true;
}

bool IsEmailAddress(string input) {
    DFA dfa;
    if (!ConstructEmailDFA(dfa)) return false;
    /* preprocess email text. */
    for (string::iterator itr = input.begin(); itr != input.end(); ++itr) {
        if (isalnum(*itr)) *itr = 'a';
        else if (*itr != '.' && *itr != '@') return false;
    }
    return SimulateDFA(dfa, input);
}

void TestDFAEmail() {
    DFA dfa;
    ConstructDFA(dfa);
    vector<string> strs = {"ac.ab@qq.com", "qq1010@qq", "0101@qq.com", ".@qq.com", ".0101@qq.com", "qq.@qq.com",
                           "t.t.@@qq.com", "qq@.com", "qq.qq.qq.qq@qq.qq.com", "qq.qq.qq.qq@qq.qq."};
    for (vector<string>::iterator itr = strs.begin(); itr != strs.end(); ++itr)
        cout << *itr << (IsEmailAddress(*itr) ? " be accepted!" : " not be accepted!") << endl;
}

/******************************* Nondeterministic Finite Automata ******************************/

/* the struct of Nondeterministic Deterministic Finite Automata. */
struct NFA {
    /* the situation where one key corresponds to many values. */
    multimap<pair<int, char>, int> transitions;
    set<int> accept_states;
    int start_state;
};

/* initialize NFA. */
/* an easy example to expound NFA. */
bool ConstructNFA(NFA &nfa) {
    nfa.transitions.insert(make_pair(make_pair(0, '0'), 0));
    nfa.transitions.insert(make_pair(make_pair(0, '0'), 1));
    nfa.transitions.insert(make_pair(make_pair(0, '1'), 0));
    nfa.transitions.insert(make_pair(make_pair(0, '1'), 3));
    nfa.transitions.insert(make_pair(make_pair(1, '0'), 2));
    nfa.transitions.insert(make_pair(make_pair(3, '1'), 4));

    nfa.start_state = 0;
    nfa.accept_states.insert(2);
    nfa.accept_states.insert(4);
    return true;
}

/* judge whether a specified a string input to be accepted or not by NFA. */
bool SimulateNFA(NFA &nfa, string input) {
    set<int> cur_states;
    cur_states.insert(nfa.start_state);
    for (string::iterator str = input.begin(); str != input.end(); ++str) {
        set<int> next_states;
        for (set<int>::iterator sta = cur_states.begin(); sta != cur_states.end(); ++sta) {
            pair<multimap<pair<int, char>, int>::iterator, multimap<pair<int, char>, int>::iterator>
                    transitions = nfa.transitions.equal_range(make_pair(*sta, *str));
            for (multimap<pair<int, char>, int>::iterator itr = transitions.first;
                 transitions.first != transitions.second; ++transitions.first) {
                next_states.insert(transitions.first->second);
            }
        }
        cur_states = next_states;
        next_states.clear();
    }
    for (set<int>::iterator itr = cur_states.begin(); itr != cur_states.end(); ++itr) {
        if (nfa.accept_states.find(*itr) != nfa.accept_states.end()) return true;
    }
    return false;
}

void TestNFA() {
    NFA nfa;
    ConstructNFA(nfa);
    vector<string> strs = {"0011", "001111010101", "0101", "0000", "010001", "0011001100"};
    for (vector<string>::iterator itr = strs.begin(); itr != strs.end(); ++itr)
        cout << *itr << (SimulateNFA(nfa, *itr) ? " be accepted!" : " not be accepted!") << endl;
}

/********************************************** Exercise Solutions *********************************************/

/* Exercise 4. */
void TestMultiSet() {
    multiset<int> ms;
    ms.insert(1);
    ms.insert(1);
    ms.insert(2);
    ms.insert(3);
    ms.insert(2);
    for (multiset<int>::iterator itr = ms.begin(); itr != ms.end(); ++itr) cout << *itr << " ";
    cout << endl;

    ms.erase(1);
    for (multiset<int>::iterator itr = ms.begin(); itr != ms.end(); ++itr) cout << *itr << " ";
    cout << endl;

}


/* Exercise 11. */
set<int> intersetion(const set<int> &s1, const set<int> &s2) {
    set<int>::iterator itr1 = s1.begin();
    set<int>::iterator itr2 = s2.begin();
    set<int> interset;
    while (itr1 != s1.end() && itr2 != s2.end()) {
        if (*itr1 == *itr2) {
            interset.insert(*itr1);
            ++itr1;
            ++itr2;
        } else if (*itr1 < *itr2) {
            ++itr1;
        } else {
            ++itr2;
        }
    }
    return interset;
}

void TestIntersetion() {
    vector<int> v1 = {1, 5, 2, 3, 7, 10};
    set<int> s1(v1.begin(), v1.end());
    vector<int> v2 = {3, 8, 2, 4, 6, 9, 10};
    set<int> s2(v2.begin(), v2.end());
    set<int> interset = intersetion(s1, s2);
    for (set<int>::iterator itr = interset.begin(); itr != interset.end(); ++itr) cout << *itr << " ";
    cout << endl;
}


/* Exercise 12. */
unsigned int RotateDiceUntilReachUpperTimes() {
    const int kUpperTimes = 3;
    const int kDiceSize = 20;
    multiset<size_t> occurances;
    unsigned int i = 0;
    while (true) {
        size_t num = (rand() % kDiceSize) + 1;
        occurances.insert(num);
        if (occurances.count(num) >= kUpperTimes) return i;
        i++;
    }
}

void TestDice() {
    int total_count = 0;
    int iter_num = 10000;
    for (int i = 0; i < iter_num; ++i) {
        int count = RotateDiceUntilReachUpperTimes();
        total_count += count;
//        cout << count << endl;
    }
    cout << "The average count is "<< total_count/iter_num << endl;
}


/* Exercise 14. */
int NumberDuplicateEntries(map<string, string> m) {
    multiset<string> ms;
    for (map<string, string>::iterator itr = m.begin(); itr != m.end(); ++itr) {
        ms.insert(itr->second);
    }
    string cur;
    size_t numDup = 0;
    bool dup = false;
    for (multiset<string>::iterator itr = ms.begin(); itr != ms.end(); ++itr) {
        dup = false;
        if (itr == ms.begin()) {
            cur = *itr;
            continue;
        }
        while (itr != ms.end() && *itr == cur) {
            dup = true;
            ++itr;
        }
        if (dup) numDup++;
        if (itr != ms.end()) cur = *itr;
        else break;
    }
    return numDup;
}

void TestNumberDuplicateEntries() {
    map<string, string> m;
    m["1"] = "11";
    m["2"] = "11";
    m["3"] = "11";
    m["4"] = "44";
    m["5"] = "55";
    m["6"] = "44";
    m["7"] = "55";
    cout << "Number of duplicate entries is " << NumberDuplicateEntries(m) << endl;
}


/* Exercise 15. */
multimap<string, string> InvertMap(map<string, string> m) {
    multimap<string, string> mm;
    for (map<string, string>::iterator itr = m.begin(); itr != m.end(); ++itr) {
        mm.insert(make_pair(itr->second, itr->first));
    }
    return mm;
}

void TestInvertMap() {
    map<string, string> m;
    m["1"] = "11";
    m["2"] = "11";
    m["3"] = "11";
    m["4"] = "44";
    m["5"] = "55";
    m["6"] = "44";
    m["7"] = "55";
    multimap<string, string> mm = InvertMap(m);
    for (multimap<string,string>::iterator itr = mm.begin(); itr != mm.end(); ++itr)
        cout << itr->first << " : " << itr->second << endl;
}


/* Exercise 16. */
map<string, string> ComposeMaps(map<string, string> one, map<string, string> two) {
    map<string, string> comp_map;
    for (map<string, string>::iterator itr = one.begin(); itr != one.end(); ++itr) {
        map<string, string>::iterator two_val_iter = two.find(itr->second);
        if (two_val_iter != two.end()) {
            comp_map[itr->first] = two_val_iter->second;
        }
    }
    return comp_map;
}

void TestComposeMaps() {
    map<string, string> one;
    one["1"] = "11";
    one["3"] = "11";
    one["4"] = "44";
    one["7"] = "55";
    map<string, string> two;
    two["11"] = "12";
    two["44"] = "0";
    two["55"] = "87";
    two["7"] = "33";
    map<string, string> comp_map = ComposeMaps(one, two);
    for (map<string,string>::iterator itr = comp_map.begin(); itr != comp_map.end(); ++itr)
        cout << itr->first << " : " << itr->second << endl;
}


/* Exercise 17. */
set<string> PrintMatchingPrefixes(set<string> &s, const string &prefix) {
    set<string> result;
    for (set<string>::iterator itr = s.begin(); itr != s.end(); ++itr) {
        cout << "Iterating " << *itr << endl;
        for (size_t i = 0; i < (*itr).size() && i < prefix.size(); ++i) {
            if ((*itr)[i] > prefix[i]) return result;
            else if ((*itr)[i] < prefix[i]) break;
            else {
                if (i == prefix.size() - 1) {
                    result.insert(*itr);
                }
            }
        }
    }
    return result;
}

void TestPrintMatchingPrefixes() {
    set<string> s;
    s.insert("abcd");
    s.insert("abce");
    s.insert("bdefg");
    s.insert( "acdfg");
    s.insert( "cdefg");
    set<string> res = PrintMatchingPrefixes(s, "ac");
    for (set<string>::iterator itr = res.begin(); itr != res.end(); ++itr) cout << *itr << endl;
}


int main() {
    TestPrintMatchingPrefixes();
//    TestComposeMaps();
//    TestInvertMap();
//    TestNumberDuplicateEntries();
//    TestDice();
//    TestIntersetion();
//    TestMultiSet();
//    TestNFA();
//    TestDFAEmail();
//    TestDFA1();
    return 0;
}
























