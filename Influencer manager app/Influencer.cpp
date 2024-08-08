#include <stdio.h>
#include "Influencer.h"

Influencer::Influencer(){
    this->name = "Unknown";
    this->followers = 0;
    this->engagementRate = 0;
    this->income = 0;
    this->participations = {"Uknown"};
}

Influencer::Influencer(const std::string& name,size_t followers,double engagementRate){
    try{
        setName(name);
        setName(name);
        this->followers = followers;
        this->engagementRate = engagementRate;
    }
    catch(const std::invalid_argument& e){
        std::cout<<e.what()<<std::endl;
    }
}


void Influencer::setName(const std::string& name){
    if(name.length() < 1)
        throw std::invalid_argument("Invalid name format!");
    this->name = name;
}


void Influencer::earnFee(double amount){
    if(amount > 0)
        income+=amount;
    else{
        throw std::invalid_argument("The amount shoudl be a postive integer!");
    }
}

void Influencer::enrollCampaign(const std::string& brand){
    if(!containsBrandName(brand))
        participations.push_back(brand);
    else{
        throw std::invalid_argument("The brand you are trying to add is already contained!");
    }
}

void Influencer::endParticipation(const std::string& brand){
    if(containsBrandName(brand)){
        std::swap(participations[getBrandIndex(brand)], participations[participations.size() - 1]);
        participations.pop_back();
    }
}


bool Influencer::containsBrandName(const std::string& name) const{
    const size_t size = participations.size();
    
    for(size_t i = 0;i<size;i++){
        if(participations[i] == name)
            return true;
    }
    return false;
}

size_t Influencer::getBrandIndex(const std::string& brand) const{
    const size_t size = participations.size();
    
    for(size_t i = 0;i<size;i++){
        if(participations[i] == brand)
            return i;
    }
    throw std::invalid_argument("Invalid brand!");
}


std::string Influencer::getName() const{
    return name;
}


size_t Influencer::getParticipationsCount() const{
    return participations.size();
}


void Influencer::sortParticipations(){
    std::sort(participations.begin(),participations.end());
}


double Influencer::getIncome() const{
    return income;
}

size_t Influencer::getFollowers() const{
    return followers;
}


void Influencer::printParticipations() const{
    const size_t size = participations.size();
    for(int i = 0;i<size;i++){
        std::cout<<participations[i]<<std::endl;
    }
}


