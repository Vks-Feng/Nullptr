#ifndef MARKETNEWS_H
#define MARKETNEWS_H

#include<QString>
#include<vector>
class MarketNews {
public:
    void addNews(QString news);
    std::vector<QString> getNews();
private:
    MarketNews();
     std::vector<QString> newsList;
//     QString Title;
//     QString context;
//     QString data;
//     QString author_name;

// public:
//     QString getTitle();
};

#endif // MARKETNEWS_H
