#include <stdio.h>
#include "CampaignRepo.h"

CampaignRepo::CampaignRepo(){
    this->capacity = 8;
    this->campaigns = new Campaign*[this->capacity];
    this->size = 0;
}

CampaignRepo::CampaignRepo(const CampaignRepo& other){
    copy(other);
}

CampaignRepo::CampaignRepo(const Campaign** campaigns,size_t size){
    this->campaigns = new Campaign*[size];
    for(int i = 0;i<size;i++)
        this->campaigns[i] = campaigns[i]->clone();
    this->size = size;
    this->capacity = size;
}

CampaignRepo::CampaignRepo(CampaignRepo&& other){
    move(std::move(other));
}

CampaignRepo& CampaignRepo::operator=(const CampaignRepo& other){
    if(this!=&other){
        destroy();
        copy(other);
    }
    return *this;
}

CampaignRepo& CampaignRepo::operator=(CampaignRepo&& other){
    if(this!=&other){
        destroy();
        move(std::move(other));
    }
    return *this;
}

CampaignRepo::~CampaignRepo(){
    destroy();
}

void CampaignRepo::destroy(){
    for(int i = 0;i<size;i++)
        delete campaigns[i];
    delete[] campaigns;
}

void CampaignRepo::move(CampaignRepo&& other){
    this->campaigns = other.campaigns;
    other.campaigns = nullptr;
    this->size = other.size;
    this->capacity = other.capacity;
    other.size = other.capacity = 0;
}

void CampaignRepo::copy(const CampaignRepo& other){
    this->campaigns = new Campaign*[other.capacity];
    for(int i = 0;i<other.size;i++)
        this->campaigns[i] = other.campaigns[i]->clone();
    this->size = other.size;
    this->capacity = other.capacity;
}

void CampaignRepo::resize(size_t newCap){
    Campaign** temp = new Campaign*[newCap];
    for(int i = 0;i<size;i++)
        temp[i] = campaigns[i];
    delete[] campaigns;
    campaigns = temp;
    this->capacity = newCap;
}


void CampaignRepo::addModel(Campaign* campaign){
    if(!containsCampaign(campaign)){
        if(size >= capacity)
            resize(capacity * 2);
        campaigns[size] = campaign;
        size++;
    }
}

bool CampaignRepo::containsCampaign(Campaign* campaign) const{
    for(int i = 0;i<size;i++){
        if(campaigns[i]->getName() == campaign->getName())
            return true;
    }
    return false;
}

Campaign* CampaignRepo::findByName(const std::string& brand) const{
    for(size_t i = 0;i<size;i++){
        if(campaigns[i]->getName() == brand)
            return campaigns[i];
    }
    return nullptr;
}

bool CampaignRepo::remove(Campaign* campaign){
    try{
        size_t index = getCampaignByIndex(campaign);
        delete campaigns[index];
        for(size_t i = index;i<size - 1;i++)
            campaigns[i] = campaigns[i+1];
        
        campaigns[size - 1] = nullptr;
        size--;
        return true;
    }
    catch(const std::invalid_argument& e){
        return false;
    }
}


size_t CampaignRepo::getCampaignByIndex(Campaign* campaign) const{
    for(int i = 0;i<size;i++){
        if(campaigns[i]->getName() == campaign->getName())
            return i;
    }
    throw std::invalid_argument("Index out of bounds!");
}
