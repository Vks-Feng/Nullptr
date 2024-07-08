#ifndef POST_H
#define POST_H
#include <QString>
#include <iostream>
#include <vector>
static int allnumber; //总帖子数量，论坛类会把这个变量通用，
//但是在每个账户的留言板会有一个自己的留言板留言数（模拟留言和回复留言功能）
class Post
{
private:
    int date; //帖子日期
    QString content; //发言内容
    QString id;   //发帖人id
    int thisid;   //本帖id号，根据构造时的allnumber更改
    int fatherid; //父帖号，如果是主帖则为0
public:
    Post(int _date,
         QString _file,
         QString _id,
         int _fatherid,
         int &_thisid = allnumber); //在留言板就可以把这个_thisid设置为用户自己的那个值
    //也可以在函数里加一个对thisid的数量限制来实现单个用户的留言板的总留言数不能超过40条等等，但其实这个最好加在user里面
    int getdate();
    QString getcontent();
    QString getid();
    int getthisid();
    int getfatherid();
};
//我还粗略的写了个展示的函数，show，详情看cpp（也许这不属于后端内容？）

#endif // POST_H
