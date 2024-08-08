#include <stdio.h>
#include "InfluencerRepo.h"

static bool compareinfluencers(Influencer* inf1,Influencer* inf2){
    if (inf1->getIncome() != inf2->getIncome()) {
           return inf1->getIncome() > inf2->getIncome();
       }
       return inf1->getFollowers() > inf2->getFollowers();
}


InfluencerRepo::InfluencerRepo(){
    this->capacity = 8;
    this->influencers = new Influencer*[this->capacity];
    this->size = 0;
}

InfluencerRepo::InfluencerRepo(const Influencer** influencers,size_t size){
    this->influencers = new Influencer*[size];
    for(int i = 0;i<size;i++)
        this->influencers[i] = influencers[i]->clone();
    
    this->size = this->capacity = size;
}

InfluencerRepo::InfluencerRepo(const InfluencerRepo& other){
    copy(other);
}

InfluencerRepo::InfluencerRepo(InfluencerRepo&& other){
    move(std::move(other));
}

InfluencerRepo& InfluencerRepo::operator=(const InfluencerRepo& other){
    if(this!=&other){
        destroy();
        copy(other);
    }
    return *this;
}

InfluencerRepo& InfluencerRepo::operator=(InfluencerRepo&& other){
    if(this!=&other){
        destroy();
        move(std::move(other));
    }
    return *this;
}


void InfluencerRepo::destroy(){
    for(int i = 0;i<size;i++)
        delete influencers[i];
    delete[] influencers;
}

void InfluencerRepo::copy(const InfluencerRepo& other){
    this->influencers = new Influencer*[other.capacity];
    for(int i = 0;i<other.size;i++){
        this->influencers[i] = other.influencers[i]->clone();
    }
    this->size = other.size;
    this->capacity = other.capacity;
}

void InfluencerRepo::move(InfluencerRepo&& other){
    this->influencers = other.influencers;
    other.influencers = nullptr;
    this->size = other.size;
    this->capacity = other.capacity;
    other.capacity = other.size = 0;
}

void InfluencerRepo::resize(size_t newCap){
    Influencer** temp = new Influencer*[newCap];
    for(int i = 0;i<size;i++){
        temp[i] = influencers[i];
    }
    delete[] influencers;
    influencers = temp;
    this->capacity = newCap;
}

InfluencerRepo::~InfluencerRepo(){
    destroy();
}

bool InfluencerRepo::containsInfluencer(Influencer* influencer) const{
    for(int i = 0;i<size;i++){
        if(influencers[i]->getName() == influencer->getName())
            return true;
    }
    return false;
}

void InfluencerRepo::addModel(Influencer* influencer){
    if(!containsInfluencer(influencer)){
        if(size >= capacity)
            resize(capacity * 2);
        
        influencers[size] = influencer;
        size++;
    }
}

bool InfluencerRepo::remove(Influencer* influencer){
    try{
        size_t index = getInfluencerIndex(influencer);
        delete influencers[index];
        influencers[index] = nullptr;
        for(size_t i = index;i<size - 1;i++)
            influencers[i] = influencers[i+1];
        
        size--;
        return true;
    }
    catch(const std::invalid_argument& e){
        return false;
    }
}

size_t InfluencerRepo::getInfluencerIndex(Influencer* influencer) const{
    for(int i = 0;i<size;i++){
        if(influencers[i]->getName() == influencer->getName())
            return i;
    }
    throw std::invalid_argument("This influencer is not contained in the list");
}


Influencer* InfluencerRepo::findByName(const std::string& name) const{
        for(int i = 0;i<size;i++){
            if(influencers[i]->getName() == name)
                return influencers[i];
        }
        return nullptr;
}


Influencer** InfluencerRepo::getInfluencers() const{
    return influencers;
}


void InfluencerRepo::sortInfluencersByIncomeThenByFollowers(){
    size_t count = getSize();
    std::sort(influencers,influencers + count,compareinfluencers);
}

size_t InfluencerRepo::getSize() const{
    return size;
}


Influencer* InfluencerRepo::getInfluencerOnIndex(size_t index) const{
    if(index > size)
        throw std::invalid_argument("Invalid index");
    return influencers[index];
}


void InfluencerRepo::printInfluencersAndActiveCampaigns(){
    for(int i = 0;i<size;i++){
        std::cout<<influencers[i]->getName() << " - "<<"Followers: " << influencers[i]->getFollowers()<<", Total income: " << influencers[i]->getIncome()<<std::endl;
        influencers[i]->sortParticipations();
        if(influencers[i]->getParticipationsCount() > 0){
            std::cout<<"Active Campaigns: "<<std::endl;
            influencers[i]->printParticipations();
        }
        
    }
}
