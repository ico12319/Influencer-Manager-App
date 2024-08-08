#pragma once
#include <iostream>
#include <vector>
#include "InfluencerType.h"

class Influencer{
protected:
    std::string name;
    size_t followers;
    double engagementRate;
    double income;
    std::vector<std::string> participations;
    
    void setName(const std::string& name);
    bool containsBrandName(const std::string& brand) const;
    size_t getBrandIndex(const std::string& brand) const;
    
public:
    Influencer();
    Influencer(const std::string& name,size_t followers,double engagementRate);
    virtual ~Influencer() = default;
    virtual Influencer* clone() const = 0;
    void earnFee(double amount);
    void enrollCampaign(const std::string& brand);
    void endParticipation(const std::string& brand);
    virtual int calculateCampaignPrice() const = 0;
    std::string getName() const;
    virtual InfluencerType getType() const = 0;
    size_t getParticipationsCount() const;
    void sortParticipations();
    double getIncome() const;
    size_t getFollowers() const;
    void printParticipations() const;
};
