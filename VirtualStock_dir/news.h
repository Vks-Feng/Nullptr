#ifndef NEWS_H
#define NEWS_H

#include<QString>
#include<QVector>
class News {

private:
    News();
    News(const News &other);
    QString title;
    QString content;
public:

    QString getTitle();
    QString getContent();

};

#endif // NEWS_H
