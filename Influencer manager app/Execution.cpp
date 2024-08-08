#include <stdio.h>
#include "Execution.h"

std::vector<std::string> formSequence(const std::string& cmd){
    std::istringstream iss(cmd);
    std::vector<std::string> tokens;
    std::string word;
    while (iss >> word) {
        tokens.push_back(word);
    }
    return tokens;
}
void start(){
    Controller controller;
    while(true){
        std::string cmd;
        std::getline(std::cin, cmd);
        std::vector<std::string> tokens = formSequence(cmd);
        std::string action = tokens[0];
        if(action == "Exit")
            break;
        else if(action == "RegisterInfluencer"){
            std::string type = tokens[1];
            std::string userName = tokens[2];
            int followers = std::stoi(tokens[3]);
            std::cout<<controller.registerInfluencer(type, userName, followers)<<std::endl;
        }
        else if(action == "BeginCampaign"){
            std::string type = tokens[1];
            std::string brand = tokens[2];
            std::cout<<controller.beginCampaign(type, brand)<<std::endl;
        }
        else if(action == "AttractInfluencer"){
            std::string brand = tokens[1];
            std::string userName = tokens[2];
            std::cout<<controller.attractInfluencer(brand, userName)<<std::endl;
        }
        else if(action == "FundCampaign"){
            std::string brand = tokens[1];
            std::string amount = tokens[2];
            std::cout<<controller.fundCampaign(brand, amount)<<std::endl;
        }
        else if(action == "CloseCampaign"){
            std::string brand = tokens[1];
            std::cout<<controller.closeCampaign(brand)<<std::endl;
        }
        else if(action == "ConcludeAppContract"){
            std::string userName = tokens[1];
            std::cout<<controller.concludeAppContract(userName)<<std::endl;
        }
        else if(action == "ApplicationReport"){
            controller.applicationReportCommand();
        }
        else{
            std::cout<<"Invalid command!"<<std::endl;
            continue;
        }
    }
    
    
}
