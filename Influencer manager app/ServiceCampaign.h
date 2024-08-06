#pragma once
#include "Campaign.h"

class ServiceCampaign : public Campaign{
    
public:
    ServiceCampaign();
    ServiceCampaign(const std::string& name);
    virtual Campaign* clone() const override;
    virtual CampaignType getType() const override;
};
