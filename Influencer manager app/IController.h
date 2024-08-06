#pragma once
#include <iostream>
#include "InfluencerRepo.h"
#include "CampaignRepo.h"
#include "BusinessInfluencer.h"
#include "FashionInfluencer.h"
#include "BloggerInfluencer.h"
#include "ProductCampaign.h"
#include "ServiceCampaign.h"

class IController{
    
public:
    virtual std::string registerInfluencer(const std::string& typeName,const std::string& userName,int followers) = 0;
    virtual std::string beginCampaign(const std::string& typeName,const std::string& brand) = 0;
    //virtual std::string fundCampaign(const std::string& brand,const std::string& amount) const = 0;
    virtual std::string attractInfluencer(const std::string& brand,const std::string& userName) const = 0;
    //virtual std::string closeCampaign(const std::string& brand) const  = 0;
    //virtual std::string concludeAppContract(const std::string& userName) const = 0;
    //virtual std::string applicationReportCommand() const = 0;
    virtual ~IController() = default;
};

