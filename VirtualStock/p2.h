
// MarketNews class
class MarketNews {
public:
    void addNews(std::string news);
    std::vector<std::string> getNews();

private:
    std::vector<std::string> newsList;
};

// RiskAssessment class
class RiskAssessment {
public:
    RiskAssessment(User& user);
    void assessRisk();
    std::string getRiskLevel();

private:
    User& user;
    std::string riskLevel;
};

// SocialFeature class
class SocialFeature {
public:
    void postMessage(std::string user, std::string message);
    std::vector<std::string> getMessages();

private:
    std::vector<std::string> messages;
};

// SimulationContest class
class SimulationContest {
public:
    void joinContest(User& user);
    void updateRankings(User& user, double portfolioValue);
    std::map<User, double> getRankings();

private:
    std::map<User, double> rankings;
};