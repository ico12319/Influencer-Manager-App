#include <stdio.h>
#include "ServiceCampaign.h"

ServiceCampaign::ServiceCampaign() : Campaign(){}

ServiceCampaign::ServiceCampaign(const std::string& name) : Campaign(name, 30000){}

Campaign* ServiceCampaign::clone() const{
    return new ServiceCampaign(*this);
}

CampaignType ServiceCampaign::getType() const{
    return CampaignType::SERVICE_CAMPAIGN;
}

