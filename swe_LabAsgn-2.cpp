#include<bits/stdc++.h>
#include"rapidxml.hpp"
#include"rapidxml_utils.hpp"
// #include"rapidxml_print.hpp"
// #include"rapidxml_iterators.hpp"
using namespace std;
using namespace rapidxml;
#define INTMAX 100000000;
class Node{
public:
  long long int id ;
  double lat,lon;
  string name;
  Node( long long x, double y, double z,string p){
    id=x;
    lat=y;
    lon=z;
    name=p;
  }
  Node(){}
};
class Way{
public:
  long long int id;
  Way(long long int a){
    id=a;
  }
  Way(){}
};


double Distance_nodes(double lat1, double lon1,
                        double lat2, double lon2)
    {
        // distance between latitudes
        // and longitudes
        double dLat = (lat2 - lat1) *
                      M_PI / 180.0;
        double dLon = (lon2 - lon1) *
                      M_PI / 180.0;
 
        // convert to radians
        lat1 = (lat1) * M_PI / 180.0;
        lat2 = (lat2) * M_PI / 180.0;
 
        // apply formulae
        double a = pow(sin(dLat / 2), 2) +
                   pow(sin(dLon / 2), 2) *
                   cos(lat1) * cos(lat2);
        double rad = 6371;
        double c = 2 * asin(sqrt(a));
        return rad * c;
    }
  
  
int main(){

//Maps which connect ids to their respective node or way .
  unordered_map<long long int,Node> nodesMap;
  unordered_map<long long int, Way> waysMap;
//Parsing from the map.osm file
  xml_document<> doc;
  std::ifstream file("map.osm");
  std::stringstream buffer;
  buffer<<file.rdbuf();
  file.close();
  std::string content(buffer.str());
  doc.parse<0>(&content[0]);

  long long numberOfnodes=0,numberOfways=0;



//PART-1**********************************************************************


  xml_node<> *X_root = doc.first_node();
  
  //for calculating number of nodes 
  for (xml_node<> *X_node= X_root->first_node("node");X_node; X_node = X_node->next_sibling("node")){
      
      Node m(stoll(X_node->first_attribute("id")->value()),stod(X_node->first_attribute("lat")->value()),stod(X_node->first_attribute("lon")->value()),"");
      nodesMap[stoll(X_node->first_attribute("id")->value())]=m;
      numberOfnodes++;

        for(xml_node<> *Z_tag=X_node->first_node("tag");Z_tag;Z_tag=Z_tag->next_sibling("tag")){
          string s1="";
          string k = Z_tag->first_attribute("k")->value();
          if(k =="name"){
           nodesMap[stoll(X_node->first_attribute("id")->value())].name =Z_tag->first_attribute("v")->value();
          }
          // if (s1.find(s2) != std::string::npos) {
          //     cout<<s1<<endl;
          // }
          // else{cout<<"k";}
      }
  }

cout<<"Enter the name of the node which you want to search:";
string s2="";
getline(cin,s2);
cout<<"\nEntered name is "<<s2<<endl<<"LIST OF SEARCHES:\n";
  

  for(auto x:nodesMap){
   if(x.second.name!=""){
     string s1= x.second.name;

     transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
     transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
  
     if (s1.find(s2) != std::string::npos) {
        cout<<x.second.name<<endl;
      }
    }
  }
  
  //for calculating number of ways
  for(xml_node<> *Y_way=X_root->first_node("way");Y_way;Y_way=Y_way->next_sibling("way")){
    Way n(stoll(Y_way->first_attribute("id")->value()));
    waysMap[stoll(Y_way->first_attribute("id")->value())]=n;
    numberOfways++;
  }
  cout<<"\nTotal number Of nodes = "<<numberOfnodes<<"\n";
  cout<<"\nTotal number Of ways = "<<numberOfways<<"\n";



//PART-2**********************************************************************


  cout<<"\nEnter the id of the node from which you want to find the k-nearest neighbours:";
  long long int node__id;
  cin>>node__id;
  cout<<"("<<node__id<<")";
  if(nodesMap.find(node__id)==nodesMap.end()){ 
    cout<<"Invalid node id!\n";
  }
  else{
    cout<<"\nEnter the value of k(k-closest neighbours)\n";
    int k;
    cin>>k;
    cout<<"("<<k<<")\nThe node ids of K-nearest neighbours are:\n";
    Node n=nodesMap[node__id];
    vector<pair<long long,long long>> A;
    
    for(auto x:nodesMap){
      if(x.first!=node__id){ 
       A.push_back(make_pair(Distance_nodes(n.lat,n.lon,x.second.lat,x.second.lon),x.first));
      }
    }
    sort(A.begin(),A.end());
    for(int i=0;i<k;i++){
      cout<<A[i].second<<endl;
    }
  }

//PART-3**********************************************************************
  cout<<"\nEnter the node ids of the two nodes of which you want to find the shortest path.\n";
  cout<<"Node Id of 1st node:\n";
  long long nodeId1,nodeId2;
  cin>>nodeId1;
  cout<<"Node Id of 2nd node:\n";
  cin>>nodeId2;
  vector<long long > B;
  for(xml_node<> *Y_way=X_root->first_node("way");Y_way;Y_way=Y_way->next_sibling("way")){
    int f1=0,f2=0;
    for(xml_node<> *Ph=Y_way->first_node("nd");Ph;Ph=Ph->next_sibling("nd")){
      if(nodeId1==stoll(Ph->first_attribute("ref")->value())) f1++;
      if(nodeId2==stoll(Ph->first_attribute("ref")->value())) f2++;
    }
    if(f1>0 && f2>0){

      B.push_back(stoll(Y_way->first_attribute("id")->value()));
    }     
  }


      
  
  










}