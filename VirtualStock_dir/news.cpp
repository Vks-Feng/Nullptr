#include "news.h"

News::News(const News&other){
    title = other.title;
    content = other.content;
}

News::News()
{
    title = nullptr;
    content = nullptr;
}

QString News::getTitle(){
    return title;
}

QString News::getContent(){
    return content;
}
