#include "post.h"

Post::Post(int _date, QString _file, QString _id, int _fatherid, int _thisid)
{
    date = _date;
    content = _file;
    id = _id;
    thisid = _thisid;
    fatherid = _fatherid;
}

int Post::getdate()
{
    return date;
}

QString Post::getcontent()
{
    return content;
}

QString Post::getid()
{
    return id;
}

int Post::getfatherid()
{
    return fatherid;
}

int Post::getthisid()
{
    return thisid;
}

void show(std::vector<Post> forum, int fathernumber = 0)
{
    //这里的fathernumber在初始化一个父帖的详情时应当为父帖的thisid
    int all = forum.size();
    for (int i = 0; i < all; i++) {
        if (forum[i].getfatherid() == fathernumber) {
            //这里就可以把对应的文本呈现到ui上
        }
    }
}
