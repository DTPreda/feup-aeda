#include "Gallery.h"
#include <ostream>
#include <algorithm>
using namespace std;

Gallery::Gallery(vector<Paint*> c): catalog(PaintCatalogItem("", "", 0, 0.00)), collection(c) {

}

vector<Paint*> Gallery::getCollection() const {
    return collection;
}

void Gallery::setCollection(vector<Paint*> c) {
    collection = c;
}

priority_queue<ExhibitionItem> Gallery::getPaintsToShow() const {
    return paintsToShow;
}
HashTableAuthorRecord Gallery::getAuthorRecords () const {
    return  authorRecords;
}

void Gallery::addAuthorRecord(AuthorRecord ar) {
    authorRecords.insert(ar);
}

void Gallery::generateCatalog() {
    catalog.makeEmpty();
    for(int i = 0; i < collection.size(); i++) {
        catalog.insert(collection[i]);
    }
}

BST<PaintCatalogItem> Gallery::getCatalog() const {
    return catalog;
}


void Gallery::prepareExhibition() {
    while( !paintsToShow.empty())
        paintsToShow.pop();
    for(int i = 0; i < collection.size(); i++) {
        ExhibitionItem ei(collection[i]);
        paintsToShow.push(ei);
    }
}

//-------------------------------------------------------------------------------

//TODO
vector<Paint*> Gallery::getPaintsBy(string a) const {
    std::vector<Paint*> res;
    BSTItrIn<PaintCatalogItem> it(catalog);
    for( ; !it.isAtEnd(); it.advance()){
        if(it.retrieve().getAuthor() == a){
            res.push_back(it.retrieve().getPaint());
        }
    }
    return res;
}

//TODO
vector<Paint*> Gallery::getPaintsBetween(int y1, int y2) const {
    vector<Paint*> tmp;
    BSTItrIn<PaintCatalogItem> it(catalog);
    for( ; !it.isAtEnd(); it.advance()){
        if(it.retrieve().getYear() >= y1 && it.retrieve().getYear() <= y2){
            tmp.push_back(it.retrieve().getPaint());
        }
    }
    return tmp;
}

//TODO
bool Gallery::updateTitle(Paint* p, string tnew) {
    if(catalog.remove(p)){
        catalog.insert(PaintCatalogItem(p->getAuthor(), tnew, p->getYear(), p->getPrice()));
        return true;
    }
    return false;
}


//TODO
int Gallery::recordAvailablePainters() { //carrega a tabela de dispersao com AuthorRecords
    int c = 0, temp;
    for(auto &painting : collection){
        if(authorRecords.count(AuthorRecord(painting->getAuthor())) == 0){
            authorRecords.insert(AuthorRecord(painting->getAuthor()));
            c++;
        }
        else {
            temp = authorRecords.find(AuthorRecord(painting->getAuthor()))->getAvailablePaints();
            authorRecords.erase(AuthorRecord(painting->getAuthor()));
            authorRecords.insert(AuthorRecord(painting->getAuthor(), temp + 1, 0));
        }
    }
    return c;
}

//TODO
double Gallery::totalSells() const {
    double val = 0;
    for(auto it = authorRecords.begin(); it != authorRecords.end(); it++){
        val += (*it).getTotalSells();
    }
    return val;
}

//TODO
double Gallery::sellPaint(string a, string t) {
    double val = -1, total; int n;
    for(auto it = collection.begin(); it != collection.end(); it++){
        if((*it)->getAuthor() == a && (*it)->getTitle() == t){
            val = (*it)->getPrice();
            break;
        }
    }
    if(val == -1){
        return 0.0;
    }
    collection.erase(remove(collection.begin(), collection.end(), Paint(a, t, 0, 0)), collection.end());
    total = authorRecords.find(AuthorRecord(a))->getTotalSells();
    n = authorRecords.find(AuthorRecord(a))->getAvailablePaints();
    authorRecords.erase(AuthorRecord(a));
    authorRecords.insert(AuthorRecord(a, n - 1, total + val));
    return val;
}

//TODO
vector<Paint*> Gallery::nBestExibition(int n, int maxPerYear) {  //escolhe as N mais caras pinturas, dos anos mais antigos, para realizar uma exposição
    vector<Paint*> tmp;
    priority_queue<ExhibitionItem> temp;
    for ( ; tmp.size() != n && !paintsToShow.empty(); paintsToShow.pop()){
        ExhibitionItem item(paintsToShow.top().getPaint());
        if(count_if(tmp.begin(), tmp.end(), [item](Paint* elem){ return elem->getYear() == item.getYear(); }) < maxPerYear){
            tmp.push_back(item.getPaint());
            continue;
        }
        temp.push(item);
    }
    while(!temp.empty()){
        paintsToShow.push(temp.top());
        temp.pop();
    }
    return tmp;
}

//TODO
int Gallery::itemExibitionOrder(string a, string t) {
    priority_queue<ExhibitionItem> temp = paintsToShow; int pos = 1;
    for ( ; !temp.empty() ; pos++){
        if(temp.top().getAuthor() == a && temp.top().getTitle() == t){
            return pos;
        }
        temp.pop();
    }
    return 0;
}

