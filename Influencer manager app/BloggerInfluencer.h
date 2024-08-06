#pragma once
#include "Influencer.h"

class BloggerInfluencer : public Influencer{
    
public:
    BloggerInfluencer();
    BloggerInfluencer(const std::string& name,size_t followers);
    virtual Influencer* clone() const override;
    virtual int calculateCampaignPrice() const override;
    virtual InfluencerType getType() const override;
};
