#include <stdio.h>
#include "Campaign.h"

Campaign::Campaign(){
    this->name = "Unknown";
    this->budget = 0;
    this->contributors = {"Unknown"};
}

Campaign::Campaign(const std::string& name,double budget){
    try{
        setName(name);
        this->budget = budget;
    }
    catch(const std::invalid_argument& e){
        std::cout<<e.what()<<std::endl;
    }
}

void Campaign::setName(const std::string& name){
    if(name.length() < 1)
        throw std::invalid_argument("Invalid name!");
    
    this->name = name;
}


void Campaign::gain(double amount){
    if(amount < 0)
        throw std::invalid_argument("The amount should be a positive number!");
    
    budget += amount;
}


void Campaign::engage(Influencer* influencer){
    double expenses = influencer->calculateCampaignPrice();
    if(budget >= expenses){
        contributors.push_back(influencer->getName());
        budget -= expenses;
    }
    else{
        throw std::logic_error("Insufficient balance!");
    }
}


std::string Campaign::getName() const{
    return name;
}


bool Campaign::containsInfluencer(Influencer* influencer) const{
    const size_t size = contributors.size();
    for(int i = 0;i<size;i++){
        if(contributors[i] == influencer->getName())
            return true;
    }
    return false;
}

double Campaign::getBudget() const{
    return budget;
}


std::vector<std::string> Campaign::getContributors() const{
    return contributors;
}
