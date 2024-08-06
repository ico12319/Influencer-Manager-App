#pragma once
#include "Campaign.h"

class ProductCampaign : public Campaign{
    
public:
    ProductCampaign();
    ProductCampaign(const std::string& brand);
    virtual Campaign* clone() const override;
    virtual CampaignType getType() const override;
};
