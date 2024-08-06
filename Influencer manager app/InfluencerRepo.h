#pragma once
#include "Influencer.h"

class InfluencerRepo{
private:
    Influencer** influencers;
    size_t size;
    size_t capacity;
    
    void copy(const InfluencerRepo& other);
    void move(InfluencerRepo&& other);
    void destroy();
    void resize(size_t newCap);
    bool containsInfluencer(Influencer* influencer) const;
    size_t getInfluencerIndex(Influencer* influencer) const;
    
public:
    InfluencerRepo();
    InfluencerRepo(const Influencer** influencers,size_t size);
    InfluencerRepo(const InfluencerRepo& other);
    InfluencerRepo(InfluencerRepo&& other);
    ~InfluencerRepo();
    InfluencerRepo& operator=(const InfluencerRepo& other);
    InfluencerRepo& operator=(InfluencerRepo&& other);
    void addModel(Influencer* influencer);
    bool remove(Influencer* influencer);
    Influencer* findByName(const std::string& name) const;
};
