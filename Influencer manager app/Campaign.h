#pragma once
#include <iostream>
#include <vector>
#include "Influencer.h"
#include "CampaignType.h"

class Campaign{
protected:
    std::string name;
    double budget;
    std::vector<std::string> contributors;
    
    void setName(const std::string& name);
    
public:
    Campaign();
    Campaign(const std::string& name,double budget);
    virtual Campaign* clone() const = 0;
    virtual ~Campaign() = default;
    std::string getName() const;
    void gain(double amount);
    void engage(Influencer* influencer);
    bool containsInfluencer(Influencer* influencer) const;
    virtual CampaignType getType() const = 0;
};
