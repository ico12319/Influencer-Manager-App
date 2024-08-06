#pragma once
#include "Campaign.h"

class CampaignRepo{
private:
    Campaign** campaigns;
    size_t size;
    size_t capacity;
    
    void copy(const CampaignRepo& other);
    void move(CampaignRepo&& other);
    void resize(size_t newCap);
    void destroy();
    bool containsCampaign(Campaign* campaign) const;
    size_t getCampaignByIndex(Campaign* campaign) const;
    
public:
    CampaignRepo();
    CampaignRepo(const Campaign** campaigns,size_t size);
    CampaignRepo(const CampaignRepo& other);
    CampaignRepo(CampaignRepo&& other);
    CampaignRepo& operator=(const CampaignRepo& other);
    CampaignRepo& operator=(CampaignRepo&& other);
    ~CampaignRepo();
    void addModel(Campaign* campaign);
    bool remove(Campaign* campaign);
    Campaign* findByName(const std::string& brand) const;
};
