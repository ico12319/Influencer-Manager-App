#include "IController.h"

class Controller : public IController{
private:
    InfluencerRepo influencers;
    CampaignRepo campaigns;
    
public:
    Controller() = default;
    Controller(const InfluencerRepo& influencers,const CampaignRepo& campaigns);
    virtual std::string registerInfluencer(const std::string& typeName,const std::string& userName,int followers) override;
    virtual std::string beginCampaign(const std::string& typeName,const std::string& brand) override;
    virtual std::string attractInfluencer(const std::string& brand,const std::string& userName) const override;
    //virtual std::string fundCampaign(const std::string& brand,const std::string& amount) const override;
    //virtual std::string closeCampaign(const std::string& brand) const  override;
    //virtual std::string concludeAppContract(const std::string& userName) const override;
    //virtual std::string applicationReportCommand() const override;
};

