#ifndef MARKETNEWS_H
#define MARKETNEWS_H

#include<QString>
#include<QVector>
class MarketNews {
public:
    void addNews(QString news);

    QVector<QString> getNews();

private:
    MarketNews();

    QVector<QString> newsList;
};

#endif // MARKETNEWS_H
