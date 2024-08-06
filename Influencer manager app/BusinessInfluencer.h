#pragma once
#include "Influencer.h"

class BusinessInfluencer : public Influencer{
    
public:
    BusinessInfluencer();
    BusinessInfluencer(const std::string& name,size_t followers);
    virtual Influencer* clone() const override;
    virtual int calculateCampaignPrice() const override;
    virtual InfluencerType getType() const override;
};
