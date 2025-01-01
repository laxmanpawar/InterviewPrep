#include <list>
#include <iostream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct ContactData {
    string name;
    string birthDate;
    vector<string> phoneNumbers;
    unsigned int lastUpdateTime;
};

vector<ContactData*>  readInput(string input) {
    list<string> inputTokens;
    stringstream inputStringStream(input);
    string token;
    while (getline(inputStringStream, token, ' ')) {
        inputTokens.push_back(token);
    }

    vector<ContactData*> contactsDataInputList;
    inputTokens.pop_front();
    while (inputTokens.size() > 0) {
        ContactData* contactData = new ContactData();
        contactData->name = inputTokens.front();
        inputTokens.pop_front();
        string birthDate = inputTokens.front();
        contactData->birthDate = birthDate != "empty" ? birthDate : "";
        inputTokens.pop_front();
        unsigned int phoneNumbersCount = stoi(inputTokens.front());
        inputTokens.pop_front();
        for (unsigned int i = 0; i < phoneNumbersCount; i++) {
            string phoneNumber = inputTokens.front();
            inputTokens.pop_front();
            if(phoneNumber == "empty") {
                phoneNumber = "";
            }
            contactData->phoneNumbers.push_back(phoneNumber);
        }
        contactData->lastUpdateTime = stoi(inputTokens.front());
        inputTokens.pop_front();
        contactsDataInputList.push_back(contactData);
    }

    return contactsDataInputList;
}

string createstringOutput(vector<ContactData*> mergedContacts)
{
    sort (mergedContacts.begin(), mergedContacts.end(),
    [] (ContactData* contactl, ContactData* contact2) {
            return contactl->name < contact2->name;
    }
    );
    stringstream output;
    for (const auto& contact: mergedContacts)
    {
        output << contact->name << " ";
        output << ((contact->birthDate != "") ? contact->birthDate : "empty") << " ";
        string phoneNumbersOutput;
        sort(contact->phoneNumbers.begin(), contact->phoneNumbers.end());
        for (const auto& phone: contact->phoneNumbers)
        {
            string phoneOutput = phone != "" ? phone : "empty";
            phoneNumbersOutput = phoneNumbersOutput + phoneOutput + " ";
        }
        
        if(phoneNumbersOutput.empty() == false)
        {
            phoneNumbersOutput.pop_back();
        }
        output << phoneNumbersOutput << " ";

        output << contact->lastUpdateTime << " ";
    }

    return output.str();
}

class DisjointSet {
    vector<int> parent, rank, size;
    
    public:
    DisjointSet(int n) {
        parent.resize(n+1);
        size.resize(n+1, 1);
        rank.resize(n+1, 0);
        for (int i = 0; i <= n; ++i) {
            parent[i] = i;
        }
    }

    int findUPar(int node) {
        if(node == parent[node]) 
            return node;

        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if(ulp_u == ulp_v) return;
        if(rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        } else if(rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        } else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if(ulp_u == ulp_v) return;
        if(size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

string mergeContacts(string input1) 
{
    auto contactsInputList = readInput(input1);

    // Write your code here
    int n = contactsInputList.size();
    DisjointSet ds(n);
    unordered_map<string, int> phoneToNodeMap;
    for(int i = 0; i < n; ++i) {
        ContactData* contact = contactsInputList[i];
        for(const auto& phone: contact->phoneNumbers) {
            if(phone == "") {
                continue;
            }
            else if(phoneToNodeMap.find(phone) == phoneToNodeMap.end()) {
                phoneToNodeMap[phone] = i;
            } else {
                ds.unionBySize(i, phoneToNodeMap[phone]);
                
                // Merge the contacts
                ContactData *contact_u = contactsInputList[phoneToNodeMap[phone]];
                ContactData *contact_v = contactsInputList[i];
                
                if(contact_u->lastUpdateTime < contact_v->lastUpdateTime) {
                    contact_u->name = contact_v->name;

                    if(contact_v->birthDate != "") {
                        contact_u->birthDate = contact_v->birthDate;
                    } else {
                        contact_v->birthDate = contact_u->birthDate;
                    }
                    contact_u->lastUpdateTime = contact_v->lastUpdateTime;
                } else {
                    contact_v->name = contact_u->name;
                    if(contact_u->birthDate != "") {
                        contact_v->birthDate = contact_u->birthDate;
                    } else {
                        contact_u->birthDate = contact_v->birthDate;
                    }
                    contact_v->lastUpdateTime = contact_u->lastUpdateTime;
                }
            }
        }
    }
    vector<ContactData*> mergedContacts;
    vector<string> mergedPhoneNumbers[n];
    for(const auto &it : phoneToNodeMap) {
        string phoneNum = it.first;
        int node = ds.findUPar(it.second);

        mergedPhoneNumbers[node].push_back(phoneNum);
    }
    for(int i = 0; i < n; ++i) {
        if (mergedPhoneNumbers[i].size() == 0) continue;
        sort(mergedPhoneNumbers[i].begin(), mergedPhoneNumbers[i].end());
        
        contactsInputList[i]->phoneNumbers = mergedPhoneNumbers[i];
        
        mergedContacts.push_back(contactsInputList[i]);
    }

    string result = createstringOutput(mergedContacts);
    result.erase(std::find_if(result.rbegin(), result.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), result.end());

    return result;
    throw "Function mergeContacts(string input1) not implemented. ";
}

int main()
{
    string input1 = "3 Alice 05-06-2006 3 12345678 empty (022)-2456-7890 5 BobParson empty 0 empty 10 AliceWisley empty 2 123456789 98765432 20";
    string result = mergeContacts(input1);
    cout << result << endl;
    return 0;
}