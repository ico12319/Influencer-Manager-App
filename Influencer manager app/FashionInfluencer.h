#pragma once
#include "Influencer.h"

class FashionInfluencer :  public Influencer{
    
public:
    FashionInfluencer();
    FashionInfluencer(const std::string& name,size_t followers);
    virtual Influencer* clone() const override;
    virtual int calculateCampaignPrice() const override;
    virtual InfluencerType getType() const override;
};
