#include <iostream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <nlohmann/json.hpp>
#include <chrono>
#include <thread>

using namespace std;
using json = nlohmann::json;

json loop(json& j){
    
    curlpp::Cleanup myCleanup;
    curlpp::Easy request;
    ostringstream response;

    request.setOpt(new curlpp::options::Url(std::string("https://pvxz88zfqg.execute-api.us-west-1.amazonaws.com/test/analysis")));

    list<string> header = 
    {
        "Content-Type: application/json",
        "accept: application/json"
    };
    
    string dataBody = j.dump();
    
    cout << "Sending " <<  dataBody << endl;
    // Set the HTTP method to POST
    request.setOpt(new curlpp::options::Post(true));
    request.setOpt(new curlpp::options::PostFields(dataBody));
    request.setOpt(new curlpp::options::PostFieldSize(dataBody.size()));
    request.setOpt(new curlpp::options::HttpHeader(header));
    request.setOpt(new curlpp::options::WriteStream(&response));
    request.perform();

    // Parse the response data as a JSON object
    json result = json::parse(response.str());
    json body = result["body"];
    json data = body["DATA"];

    // Print the JSON object
    // cout << result << std::endl;

    return result["DATA"];
}

int main(){

    json j;
    json data;
    data["FIELD1"] = "NEW_DATA";
    data["FIELD2"] = "ULENO_TEST";
    data["FIELD3"] = "3000";

    json body;
    body["DATA"] = data;

    j["body"] = body;
    bool condition = true;

    while (condition){    
        body["DATA"] = loop(j);
        j["body"] = body;

        cout << "Received " << j << endl;
        cout << "20 seconds interval" << endl;
        this_thread::sleep_for(chrono::seconds(20));
        cout << endl;
    }
    return 1;
}