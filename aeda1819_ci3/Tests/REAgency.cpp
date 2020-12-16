#include "REAgency.h"
#include <algorithm>

REAgency::REAgency(): catalogItems(PropertyTypeItem("", "","", 0)) {
	//do nothing!
}

REAgency::REAgency(vector<Property*> properties): catalogItems(PropertyTypeItem("", "","", 0)) {
	this->properties = properties;
}

void REAgency::addProperty(Property* property) {
	this->properties.push_back(property);
}

void REAgency::addProperties(vector<Property*> properties) {
	this->properties = properties;
}

vector<Property*> REAgency::getProperties() const{
	return this->properties;
}

PropertyTypeItem REAgency::getTypeItem(string address, string postalCode, string typology) {
	PropertyTypeItem itemNotFound("", "", "", 0);
	BSTItrIn<PropertyTypeItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getAddress() == address && it.retrieve().getPostalCode() == postalCode && it.retrieve().getTypology() == typology) {
			PropertyTypeItem pti(it.retrieve().getAddress(), it.retrieve().getPostalCode(), it.retrieve().getTypology(), 0);
			pti.setItems(it.retrieve().getItems());
			return pti;
		}
		it.advance();
	}
	return itemNotFound;
}

void REAgency::addTypeItem(Property* property) {
	PropertyTypeItem itemNotFound("", "","", 0);
	PropertyTypeItem pti(property->getAddress(), property->getPostalCode(), property->getTypology(), property->	getPrice());
	PropertyTypeItem ptiX = catalogItems.find(pti);
	if(ptiX == itemNotFound) {
		pti.addItems(property);
		this->catalogItems.insert(pti);
	}
	else {
		this->catalogItems.remove(ptiX);
		ptiX.addItems(property);
		this->catalogItems.insert(ptiX);
	}
	properties.push_back(property);
}

BST<PropertyTypeItem> REAgency::getTypeItems() const {
	return this->catalogItems;
}

vector<ClientRecord> REAgency::getClientRecords() const {
	vector<ClientRecord> records;
	HashTabClientRecord::const_iterator it1 = this->listingRecords.begin();
	HashTabClientRecord::const_iterator it2 = this->listingRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void REAgency::setClientRecords(vector<ClientRecord>& crs) {
	for(unsigned int i = 0; i < crs.size(); i++) {
		listingRecords.insert(crs[i]);
	}

}

priority_queue<Client> REAgency::getClientProfiles() const {
	return clientProfiles;
}
void REAgency::setClientProfiles(priority_queue<Client>& profiles) {
	clientProfiles = profiles;
}

//
// TODO: Part I   - BST
//
void REAgency::generateCatalog() {
	vector<PropertyTypeItem> items; bool check;
    sort(properties.begin(), properties.end(), [](Property* first, Property* second){ return first->getPrice() > second->getPrice(); });
	for(auto &item : properties){
	    check = false;
	    for(auto & it : items){
	        if(it.getTypology() == item->getTypology() && it.getAddress() == item->getAddress() && it.getPostalCode() == item->getPostalCode()){
                it.addItems(item);
                check = true;
                break;
	        }
	    }
	    if(!check){
	        items.push_back(PropertyTypeItem(item->getAddress(), item->getPostalCode(), item->getTypology(), item->getPrice()));
	        items[items.size() - 1].addItems(item);
	    }
	}
	for(auto &elem : items){
	    catalogItems.insert(elem);
	}
}

vector<Property*> REAgency::getAvailableProperties(Property* property) const {
	vector<Property*> temp = catalogItems.find(PropertyTypeItem(property->getAddress(), property->getPostalCode(), property->getTypology(), 0)).getItems();
	temp.erase(remove_if(temp.begin(), temp.end(), [](Property* elem){ return get<0>(elem->getReservation()) != NULL; }), temp.end());
	return temp;
}

bool REAgency::reservePropertyFromCatalog(Property* property, Client* client, int percentage) {
	vector<Property*> props = getAvailableProperties(property);
	if(!props.empty()){
	    props[0]->setReservation(make_tuple(client, props[0]->getPrice() - props[0]->getPrice() * percentage/100));
	    return true;
	}
	return false;
}

void REAgency::addClientRecord(Client* client) {
    listingRecords.insert(ClientRecord(client));
}

void REAgency::deleteClients() {
    for(auto it = listingRecords.begin(); it != listingRecords.end(); it++){
        if(it->getClientPointer()->getVisitedProperties().empty()){
            listingRecords.erase(it);
            return deleteClients();
        }
    }
}

//
// TODO: Part III - Priority Queue
//
void REAgency::addBestClientProfiles(const vector<Client>candidates, int min) {
    double counter;
    for(auto &client : candidates){
        counter = 0;
        for(auto &prop : properties){
            if(get<0>(prop->getReservation()) != NULL){
                if(get<0>(prop->getReservation())->getName() == client.getName()){
                    counter += 1;
                }
            }
        }
        if(counter/((double)client.getVisitedProperties().size()) > min){
            clientProfiles.push(client);
        }
    }
}

vector<Property*> REAgency::suggestProperties() {
	vector<Property*> tempProperties; priority_queue<Client> temp = clientProfiles; int dif;
    int index;
	while(!temp.empty()){
	    if(!get<0>(temp.top().getVisiting()).empty()){
	        dif = INT32_MAX; index = 0;
	        for(int i = 0; i < properties.size(); i++){
	            if(stoi(properties[i]->getPostalCode()) - stoi(get<1>(temp.top().getVisiting())) < dif){
                    index = i;
	            }
	        }
	        tempProperties.push_back(properties[index]);
	    }
	    temp.pop();
	}
	return tempProperties;
}
