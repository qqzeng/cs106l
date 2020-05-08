#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>
#include <ctime>
#include "SimpleGraph.h"

using std::cout;    using std::endl;    using std::string;
using std::ifstream;     using std::cin;      using std::cerr;
using std::stringstream;     using std::vector;

const double kPi = 3.14159265358979323;
const double kRepel = 0.01;
const double kAttract = 0.001;

void Welcome();

void OpenFile(ifstream &myStream);

void InitSG(struct SimpleGraph &sg, int &timeLimit);

void PrintSG(struct SimpleGraph &sg);

int GetInteger();

string GetLine();
void InitPlacement(struct SimpleGraph &sg);
void ComputeNetForces(struct SimpleGraph &sg);

void UpdateSG(struct SimpleGraph &sg, const int timeLimit);

void MoveSGNode(struct SimpleGraph &sg, vector<double> &deltaXs, vector<double> &deltaYs);

/************ Extension implementations. ***************/
void AddRandomPerturbationsForNode(double &deltaX, double &deltaY);
void ComputeNetForcesWithRandomPerturbations(struct SimpleGraph &sg);

// Main method
int main() {
    /* 1. Display welcoming message. */
    Welcome();
    bool continued = true;
    while (continued) {
        vector<Node> nodes;
        vector<Edge> edges;
        struct SimpleGraph sg;
        sg.nodes = nodes;
        sg.edges = edges;
        int timeLimit;
        /* 2. Load and print the simple graph from disk file. */
        InitSG(sg, timeLimit);
//        PrintSG(sg);
        /* 3. Init and draw the initial simple graph. */
        InitPlacement(sg);
        InitGraphVisualizer(sg);
        DrawGraph(sg);
        /* 4. Draw the simple graph gradually. */
        UpdateSG(sg, timeLimit);
        cout << "Press 1 to continue another figure simulation, otherwise terminated !" << endl;
        continued = GetInteger() == 1;
    }
    cout << "Byte ..." << endl;
    return 0;
}

/* Prints a message to the console welcoming the user and
 * describing the program. */
void Welcome() {
    cout << "Welcome to CS106L GraphViz!" << endl;
    cout << "This program uses a force-directed graph layout algorithm" << endl;
    cout << "to render sleek, snazzy pictures of various graphs." << endl;
    cout << endl;
}

/*
 * input a string value from standard input representing the file name,
 * read its content if valid.
 */
void InitSG(struct SimpleGraph &sg, int &timeLimit) {
    ifstream myStream;
    OpenFile(myStream);
    std::size_t nodeNum;
    myStream >> nodeNum;
    for (unsigned i = 0; i < nodeNum; ++i) {
        sg.nodes.push_back(Node{x:0, y:0});
    }
    std::size_t start, end;
    while (myStream >> start >> end) {
        sg.edges.push_back(Edge{start:start, end:end});
    }
    cout << "Please set the number of seconds to run the algorithm: " << endl;
    timeLimit = GetInteger();
}

/*
 * input a integer value from standard input until user enter a valid value.
 */
int GetInteger() {
    while (true) {
        stringstream converter;
        converter << GetLine();
        int result;
        if (converter >> result) {
            char remaining;
            if (converter >> remaining) // Something's left, input is invalid
                cout << "Unexpected character: " << remaining << endl;
            else
                return result;
        } else
            cout << "Please enter an integer, Retry: " << endl;
    }
}

/* Read a line from standard input. */
string GetLine() {
    string result;
    getline(cin, result);
    return result;
}

/*
 * Open a file by given its input file stream and return it if it indeed exists.
 */
void OpenFile(ifstream &myStream) {
    cout << "Please enter the file name: " << endl;
    string fileName;
    while (true) {
//        cin >> fileName;
        fileName = GetLine();
        cout << "Ready to open file " << fileName << endl;
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

/*
 * Print the SimpleGraph.
 */
void PrintSG(struct SimpleGraph &sg) {
    std::size_t nodeNum = sg.nodes.size();
    cout << "node size of simplegraph is " << nodeNum << endl;
    for (int i = 0; i < sg.edges.size(); ++i) {
        cout << sg.edges[i].start << " " << sg.edges[i].end << endl;
    }
}

/* Set up the position the nodes initially. */
void InitPlacement(struct SimpleGraph &sg) {
    int nodeNum = sg.nodes.size();
    for (int i = 0; i < nodeNum; ++i) {
        sg.nodes[i].x = cos(2 * kPi * i / nodeNum);
        sg.nodes[i].y = sin(2 * kPi * i / nodeNum);
    }
}

/* Update the position the nodes iteratively. */
void UpdateSG(struct SimpleGraph &sg, const int timeLimit) {
    time_t startTime = time(NULL);
    while (true) {
        /* 4. Compute the net forces on each node. */
//        ComputeNetForces(sg);
        ComputeNetForcesWithRandomPerturbations(sg);
         /* 5. Update and draw the simple graph. */
        DrawGraph(sg);
        double elapsedTime = difftime(time(NULL), startTime);
        if (elapsedTime > timeLimit) break;
    }
    cout << "Simulation case completed!" << endl;
}

/* Compute the net forces on each node. */
void ComputeNetForces(struct SimpleGraph &sg) {
    /* 1.1. Compute the repulsive forces on each node. */
    vector<Node> nodes = sg.nodes;
    vector<Edge> edges = sg.edges;
    for (int i = 0; i < nodes.size(); ++i) {
        for (int j = i + 1; j < nodes.size(); ++j) {
            Node n1 = sg.nodes[i];
            Node n2 = sg.nodes[j];
            double fRepl = kRepel / sqrt((n2.y - n1.y) * (n2.y - n1.y) + (n2.x - n1.x) * (n2.x - n1.x));
            double theta = atan2(n2.y - n1.y, n2.x - n1.x);
            double deltaX1 = 0, deltaY1 = 0, deltaX2 = 0, deltaY2 = 0;
            deltaX1 -= fRepl * cos(theta);
            deltaY1 -= fRepl * sin(theta);
            deltaX2 += fRepl * cos(theta);
            deltaY2 += fRepl * sin(theta);
            nodes[i].x += deltaX1;
            nodes[i].y += deltaY1;
            nodes[j].x += deltaX2;
            nodes[j].y += deltaY2;
            sg.nodes = nodes;
        }
    }
    /* 1.2. Compute the attractive forces on each node. */
    for (int k = 0; k < sg.edges.size(); ++k) {
        int i = sg.edges[k].start;
        int j = sg.edges[k].end;
        Node n1 = sg.nodes[i];
        Node n2 = sg.nodes[j];
        double fAttr = kAttract * ((n2.y - n1.y) * (n2.y - n1.y) + (n2.x - n1.x) * (n2.x - n1.x));
        double theta = atan2(n2.y - n1.y, n2.x - n1.x);
        double deltaX1 = 0, deltaY1 = 0, deltaX2 = 0, deltaY2 = 0;
        deltaX1 += fAttr * cos(theta);
        deltaY1 += fAttr * sin(theta);
        deltaX2 -= fAttr * cos(theta);
        deltaY2 -= fAttr * sin(theta);
        nodes[i].x += deltaX1;
        nodes[i].y += deltaY1;
        nodes[j].x += deltaX2;
        nodes[j].y += deltaY2;
        sg.nodes = nodes;
    }
}

/* Move each node by the specified amount. */
void MoveSGNode(struct SimpleGraph &sg, vector<double> &deltaXs, vector<double> &deltaYs) {
    for (int i = 0; i < sg.nodes.size(); ++i) {
        sg.nodes[i].x += deltaXs[i];
        sg.nodes[i].y += deltaYs[i];
    }
}

/* Extension 2. Add random perturbations.*/
void ComputeNetForcesWithRandomPerturbations(struct SimpleGraph &sg) {
    /* 1.1. Compute the repulsive forces on each node. */
    vector<Node> nodes = sg.nodes;
    vector<Edge> edges = sg.edges;
    for (int i = 0; i < nodes.size(); ++i) {
        for (int j = i + 1; j < nodes.size(); ++j) {
            Node n1 = sg.nodes[i];
            Node n2 = sg.nodes[j];
            double fRepl = kRepel / sqrt((n2.y - n1.y) * (n2.y - n1.y) + (n2.x - n1.x) * (n2.x - n1.x));
            double theta = atan2(n2.y - n1.y, n2.x - n1.x);
            double deltaX1 = 0, deltaY1 = 0, deltaX2 = 0, deltaY2 = 0;
            deltaX1 -= fRepl * cos(theta);
            deltaY1 -= fRepl * sin(theta);
            deltaX2 += fRepl * cos(theta);
            deltaY2 += fRepl * sin(theta);
            nodes[i].x += deltaX1;
            nodes[i].y += deltaY1;
            nodes[j].x += deltaX2;
            nodes[j].y += deltaY2;
            double deltaX = 0.0, deltaY = 0.0;
            AddRandomPerturbationsForNode(deltaX, deltaY);
            nodes[i].x += deltaX;
            nodes[i].y += deltaY;
            deltaX = 0.0, deltaY = 0.0;
            AddRandomPerturbationsForNode(deltaX, deltaY);
            nodes[j].x += deltaX;
            nodes[j].y += deltaY;
            sg.nodes = nodes;
        }
    }
    /* 1.2. Compute the attractive forces on each node. */
    for (int k = 0; k < sg.edges.size(); ++k) {
        int i = sg.edges[k].start;
        int j = sg.edges[k].end;
        Node n1 = sg.nodes[i];
        Node n2 = sg.nodes[j];
        double fAttr = kAttract * ((n2.y - n1.y) * (n2.y - n1.y) + (n2.x - n1.x) * (n2.x - n1.x));
        double theta = atan2(n2.y - n1.y, n2.x - n1.x);
        double deltaX1 = 0, deltaY1 = 0, deltaX2 = 0, deltaY2 = 0;
        deltaX1 += fAttr * cos(theta);
        deltaY1 += fAttr * sin(theta);
        deltaX2 -= fAttr * cos(theta);
        deltaY2 -= fAttr * sin(theta);
        nodes[i].x += deltaX1;
        nodes[i].y += deltaY1;
        nodes[j].x += deltaX2;
        nodes[j].y += deltaY2;
        sg.nodes = nodes;
    }
}

void AddRandomPerturbationsForNode(double &deltaX, double &deltaY) {
    srand(static_cast<unsigned int>(time(NULL)));
    double slightForceDire = (rand() % 10) / static_cast<double>(10.0) * 2 * kPi;
    double fPerturbation = (rand() % 10) / static_cast<double>(1000.0);
    deltaX = fPerturbation * cos(slightForceDire);
    deltaY = fPerturbation * sin(slightForceDire);
}


