#include "function.h"

#include <iostream>
#include <list>

using namespace std;

void Implement::addEdge(const int label_1, const int label_2 , const int weight){
    if(label_1==label_2 || label_1<0 || label_1>99 || label_2<0 || label_2>99) return;
    int isEnd = 0;  //0:nothing done, 1:vertex_1 done, 2:vertex_2 done, 3:both vertex done
    bool isExist = false;
    list<Vertex>::iterator itV = VertexArr.begin();
    list<Neighbor>::iterator itN;
    while(itV!=VertexArr.end() && isExist!=true) { //check if vertex exist
        if(itV->label == label_1) {  //if vertex_1 is exist
            itN = itV->neighbors.begin();
            while(itN != itV->neighbors.end()) {  //check if neighbor exist vertex_2
                if(itN->label == label_2) {
                    isExist = true;
                    break;
                }
                itN++;
            }
            if(isExist != true) {  //if vertex_2 is not neighbor
                itV->neighbors.push_back(Neighbor(label_2, weight));
                itV->v_degree++;
            }
            if(isEnd == 0) isEnd = 1;
            else if(isEnd == 2) isEnd = 3;
        }else if(itV->label == label_2) {  //if vertex_2 is exist
            itN = itV->neighbors.begin();
            while(itN != itV->neighbors.end()) {  //check if neighbor exist vertex_1
                if(itN->label == label_1) {
                    isExist = true;
                    break;
                }
                itN++;
            }
            if(isExist != true) { //if vertex_1 is not neighbor
                itV->neighbors.push_back(Neighbor(label_1, weight));
                itV->v_degree++;
            }
            if(isEnd == 0) isEnd = 2;
            else if(isEnd == 1) isEnd = 3;
        }
        itV++;
    }
    if(isExist!=true && isEnd!=3) {  //missing vertex
        if(isEnd == 0) {  // missing both vertex_1 & vertex_2
            Vertex newV1, newV2;
            newV1 = Vertex(label_1);
            newV1.neighbors.push_back(Neighbor(label_2, weight));
            VertexArr.push_back(newV1);
            newV2 = Vertex(label_2);
            newV2.neighbors.push_back(Neighbor(label_1, weight));
            VertexArr.push_back(newV2);
        }else if(isEnd == 1) { //missing vertex_2
            Vertex newV;
            newV = Vertex(label_2);
            newV.neighbors.push_back(Neighbor(label_1, weight));
            VertexArr.push_back(newV);
        }else if(isEnd == 2) { //missing vertex_1
            Vertex newV;
            newV = Vertex(label_1);
            newV.neighbors.push_back(Neighbor(label_2, weight));
            VertexArr.push_back(newV);
        }
    }
}

void Implement::deleteEdge(const int label_1, const int label_2){
    if(VertexArr.empty() || label_1<0 || label_1>99 || label_2<0 || label_2>99) return;
    list<Vertex>::iterator itV, itV1, itV2;
    int isEnd = 0;  //0:both vertex not found, 1:vertex_1 found, 2:vertex_2 found, 3:both vertex found
    itV = VertexArr.begin();
    while(itV!=VertexArr.end() && isEnd!=3) {  //check if vertex exist
        if(itV->label == label_1) {  //if vertex_1 is exist
            itV1 = itV;
            if(isEnd == 0) isEnd = 1;
            else if(isEnd == 2) isEnd = 3;
        }else if(itV->label == label_2) {  //if vertex_2 is exist
            itV2 = itV;
            if(isEnd == 0) isEnd = 2;
            else if(isEnd == 1) isEnd = 3;
        }
        itV++;
    }
    if(isEnd == 3) {  //both vertex are exist, delete edge if exist
        list<Neighbor>::iterator itN;
        itN = itV1->neighbors.begin();
        while(itN!=itV1->neighbors.end()) {  //delete edge from vertex_1->neighbors
            if(itN->label == label_2) {
                itV1->neighbors.erase(itN);
                itV1->v_degree--;
                break;
            }
            itN++;
        }
        itN = itV2->neighbors.begin();
        while(itN!=itV2->neighbors.end()) {  //delete edge from vertex_2->neighbors
            if(itN->label == label_1) {
                itV2->neighbors.erase(itN);
                itV2->v_degree--;
                break;
            }
            itN++;
        }
    }
}

void Implement::deleteVertex(const int label){
    if(VertexArr.empty() || label<0 || label>99) return;
    list<Vertex>::iterator itV = VertexArr.begin();
    bool isFound = false;
    while(itV!=VertexArr.end()) {  //find vertex
        if(itV->label == label) {
            isFound = true;
            break;
        }
        itV++;
    }
    if(isFound == true) {  //if vertex exist
        list<Neighbor>::iterator itN = itV->neighbors.begin();
        while(itN!=itV->neighbors.end()) {  //delete all edges related to this vertex
            deleteEdge(label, itN->label);
            itN = itV->neighbors.begin();
        }
        VertexArr.erase(itV);
    }
}

int Implement::degree(const int label){
    list<Vertex>::iterator itV = VertexArr.begin();
    while(itV!=VertexArr.end()) {
        if(itV->label == label) return itV->v_degree;
        itV++;
    }
    return 0;
}

bool Implement::isExistPath(const int label_1, const int label_2){
    if(VertexArr.empty() || label_1<0 || label_1>99 || label_2<0 || label_2>99 || label_1==label_2) return false;
    list<Vertex>::iterator itV, itV1;
    int isEnd = 0;  //0:both vertex not found, 1:vertex_1 found, 2:vertex_2 found, 3:both vertex found
    itV = VertexArr.begin();
    while(itV!=VertexArr.end() && isEnd!=3) {  //check if vertex exist
        if(itV->label == label_1) {  //if vertex_1 is exist
            itV1 = itV;
            if(isEnd == 0) isEnd = 1;
            else if(isEnd == 2) isEnd = 3;
        }else if(itV->label == label_2) {  //if vertex_2 is exist
            if(isEnd == 0) isEnd = 2;
            else if(isEnd == 1) isEnd = 3;
        }
        itV++;
    }
    if(isEnd == 3) {  //if both vertex found
        int is_visited[100] = {0};  //save if vertex visited or not
        list<int> vList;  //the vertex waiting for visit
        is_visited[label_1] = 1;
        vList.push_back(label_1);
        list<Neighbor>::iterator check;
        int temp;
        while(!vList.empty()) {  //check all possible path
            temp = vList.front();
            vList.erase(vList.begin());
            if(temp == label_1) {
                itV = itV1;
                check = itV->neighbors.begin();
            }
            else {
                itV = VertexArr.begin();
                while(itV!=VertexArr.end()) {
                    if(itV->label == temp) {
                        check = itV->neighbors.begin();
                        break;
                    }
                    itV++;
                }
            }
            while(check!=itV->neighbors.end()) {
                if(check->label == label_2) return true;
                if(is_visited[check->label]==0) {
                    is_visited[check->label] = 1;
                    vList.push_back(check->label);
                }
                check++;
            }
        }
    }
    return false;
}

void Implement::deleteGraph(){
    VertexArr.clear();
}

int Implement::number_of_component(){
    if(VertexArr.empty()) return 0;  //check if empty
    int is_visited[100] = {0};  //save if vertex visited or not
    list<int> vList;
    list<int>::iterator check;
    list<Vertex>::iterator itV = VertexArr.begin();
    while(itV!=VertexArr.end()) {  //get all vertex
        vList.push_back(itV->label);
        itV++;
    }
    if(vList.size()==1) return 1;  //only exist one vertex
    int i, startV, endV, NoC=0;
    /*
        check all the vertex whether with start_vertex in the same component or not
        if not, there exist other component
        break out and change another start_vertex
    */
    while(!vList.empty()) {
        startV = vList.front();
        vList.erase(vList.begin());
        is_visited[startV] = 1;
        while(1) {
            if(!vList.empty()) {
                endV = vList.front();
                vList.erase(vList.begin());
            }else return NoC+1;
            is_visited[endV] = 1;
            if(!isExistPath(startV, endV)) vList.push_back(endV);
            check = vList.begin();
            while(check!=vList.end()) {
                if(is_visited[(*check)]==0) break;  //some vertex are not checked with start_vertex yet
                check++;
            }
            if(check==vList.end()) {  //all vertex are checked with start_vertex
                for(i=0;i<100;i++) is_visited[i]=0;  //initialize for next start vertex
                NoC++;
                break;
            }
        }
    }
    return NoC;
}

bool Implement::isExistCycle() {
    if(VertexArr.empty()) return false;
    list<Vertex>::iterator itV, itVV;
    list<Neighbor>::iterator itN, check;
    int temp, i, j;
    int is_visited[100][100];  //save if edge visited or not
    list<int> vList;  //the vertex waiting for visit
    itV = VertexArr.begin();
    for(i=0;i<100;i++) {
        for(j=0;j<100;j++) is_visited[i][j] = 0;
    }
    while(itV!=VertexArr.end()) {  //check all vertex
        itN = itV->neighbors.begin();
        while(itN!=itV->neighbors.end()) {  //check all neighbors in this vertex
            is_visited[itV->label][itN->label] = 1;
            is_visited[itN->label][itV->label] = 1;
            vList.push_back(itN->label);
            while(!vList.empty()) {
                temp = vList.front();
                vList.erase(vList.begin());
                itVV = VertexArr.begin();
                while(itVV!=VertexArr.end()) {  //Neighbors of the vertices' neighbors
                    if(itVV->label == temp) {
                        check = itVV->neighbors.begin();
                        break;
                    }
                    itVV++;
                }
                while(check!=itVV->neighbors.end()) {
                    if(check->label==itV->label && is_visited[itVV->label][check->label]!=1) return true;
                    if(is_visited[itVV->label][check->label]==0) {  //add this vertex in the check list
                        is_visited[itVV->label][check->label] = 1;
                        is_visited[check->label][itVV->label] = 1;
                        vList.push_back(check->label);
                    }
                    check++;
                }
            }
            for(i=0;i<100;i++) {  //initialize for next check
                for(j=0;j<100;j++) is_visited[i][j] = 0;
            }
            itN++;
        }
        itV++;
    }
    return false;
}
