#include "backdb.h"
#include "QString"
#include <string>
#include <QDebug>
#include "user.h"
#include "record.h"
#include "portfolio.h"
#include "stock.h"
#include "post.h"


// The implement of backEndWithDataBase Class

//----------Constructor----------

//Constructor , the basic information is host+user+password+database
BackDB::BackDB(const char* _host, const  char* _user, const  char* _password, const  char* _database,
                                         unsigned int _port, const char* _unix_socket , unsigned long _client_flag)
    :host(_host), user(_user), password(_password), database(_database), port(_port), unix_socket(_unix_socket)
    , client_flag(_client_flag)
{
    mysql_init(&mysql);

    // Connect to MySQL database using mysql_real_connect
    if (mysql_real_connect(&mysql, host, user, password, database, port, unix_socket, client_flag))
    {
        std::cout << "Connected to MySQL database successfully!" << std::endl;
        std::cout << "Database Name:" << database << std::endl;

    }
    else {
        std::cerr << "Connection error: " << mysql_error(&mysql) << std::endl;
    }

}

//Usually you use these function instead of using the constructor directorly
BackDB::BackDB()
{
    const char* host = "rm-n4a8f71b4zhg4w616co.mysql.cn-wuhan-lr.rds.aliyuncs.com"; // MySQL server host
    const char* user = "visitor_1"; // MySQL username
    const char* password = "VirtualStocks123"; // MySQL password
    const char* database = "stocks"; // MySQL database name
    unsigned int port = 3306; // MySQL port (default is 3306)
    const char* unix_socket = nullptr; // Unix socket (can be nullptr for TCP/IP)
    unsigned long client_flag = 0; // Connection flags (usually 0)

    mysql_init(&mysql);

    // Connect to MySQL database using mysql_real_connect
    if (mysql_real_connect(&mysql, host, user, password, database, port, unix_socket, client_flag)) {
        std::cout << "Connected to MySQL database successfully!" << std::endl;
        std::cout << "Database Name:" << database << std::endl;

    }
    else {
        std::cerr << "Connection error: " << mysql_error(&mysql) << std::endl;
    }

}

//----------Constructor----------



//----------Basic Operations----------

//Return the MYSQL_RES Pointer of the return result
MYSQL_RES* BackDB::query(const char* query)
{
    int ret = mysql_query(&mysql, query);

    //If the query cannot perform well
    if (ret != 0) {
        std::cerr << "Query execution failed: " << mysql_error(&mysql) << std::endl;
        return nullptr;
    }

    //If perform well
    else {
        // Query executed successfully, handle results
        MYSQL_RES* result = mysql_store_result(&mysql);

        //If the result set is NULL
         if (result == nullptr) {
            std::cout << "Don't have the result set(not necessary) " << std::endl;
         }
        return result;
    }
}

//Here is my fault,maybe I should replace all the char* with QString??
MYSQL_RES* BackDB::query(QString qStr)
{
    QByteArray byteArray = qStr.toUtf8();
    const char* query = byteArray.data();
    return this->query(query);
}

//Show the origin information of the table,
//return -1 if fails,else return the number of the rows
QString BackDB::showQuery(const char* query)
{
    // Assuming 'mysql' is already initialized and connected properly
    QString StringReturn;
    int ret = mysql_query(&mysql, query);

    if (ret != 0) {
        std::cerr << "Query execution failed: " << mysql_error(&mysql) << std::endl;
        StringReturn = "Query execution failed:";
        return StringReturn;
    }
    else {
        // Query executed successfully, handle results
        MYSQL_RES* result = mysql_store_result(&mysql);

        if (result == nullptr) {
            std::cerr << "Failed to get the result set" << std::endl;
        }
        else {
            // Process the result set if needed
            int num_fields = mysql_num_fields(result);
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result))) {
               for (int i = 0; i < num_fields; i++) {
                   std::cout << row[i] << " ";
                   StringReturn.append(row[i]);
                   StringReturn.append(" ");
               }
                   StringReturn.append("\n");
                   std::cout << std::endl;
            }
        }
        return StringReturn;
    }
}

QString BackDB::showQuery(QString qStr)
{
    QByteArray byteArray = qStr.toUtf8();
    const char* query = byteArray.data();
    this->showQuery(query);
}

const char* field_type_to_string(enum_field_types type) {
    switch (type) {
    case MYSQL_TYPE_DECIMAL:      return "DECIMAL";
    case MYSQL_TYPE_TINY:         return "TINYINT";
    case MYSQL_TYPE_SHORT:        return "SMALLINT";
    case MYSQL_TYPE_LONG:         return "INT";
    case MYSQL_TYPE_FLOAT:        return "FLOAT";
    case MYSQL_TYPE_DOUBLE:       return "DOUBLE";
    case MYSQL_TYPE_NULL:         return "NULL";
    case MYSQL_TYPE_TIMESTAMP:    return "TIMESTAMP";
    case MYSQL_TYPE_LONGLONG:     return "BIGINT";
    case MYSQL_TYPE_INT24:        return "MEDIUMINT";
    case MYSQL_TYPE_DATE:         return "DATE";
    case MYSQL_TYPE_TIME:         return "TIME";
    case MYSQL_TYPE_DATETIME:     return "DATETIME";
    case MYSQL_TYPE_YEAR:         return "YEAR";
    case MYSQL_TYPE_NEWDATE:      return "NEWDATE";
    case MYSQL_TYPE_VARCHAR:      return "VARCHAR";
    case MYSQL_TYPE_BIT:          return "BIT";
    case MYSQL_TYPE_JSON:         return "JSON";
    case MYSQL_TYPE_NEWDECIMAL:   return "NEWDECIMAL";
    case MYSQL_TYPE_ENUM:         return "ENUM";
    case MYSQL_TYPE_SET:          return "SET";
    case MYSQL_TYPE_TINY_BLOB:    return "TINYBLOB";
    case MYSQL_TYPE_MEDIUM_BLOB:  return "MEDIUMBLOB";
    case MYSQL_TYPE_LONG_BLOB:    return "LONGBLOB";
    case MYSQL_TYPE_BLOB:         return "BLOB";
    case MYSQL_TYPE_VAR_STRING:   return "VAR_STRING";
    case MYSQL_TYPE_STRING:       return "STRING";
    case MYSQL_TYPE_GEOMETRY:     return "GEOMETRY";
    default:                      return "UNKNOWN";
    }
}

void BackDB::tableDesc(const char* tableName) {
    // Using std::string to concatenate
    std::string result = "SELECT * FROM " + std::string(tableName) + " LIMIT 1";
    const char* _query = result.c_str();

    MYSQL_RES* queryResult = query(_query);
    if (queryResult == NULL) {
        std::cerr << "Query failed: " << mysql_error(&mysql) << std::endl;
        return;
    }

    unsigned int num_fields;
    unsigned int i;
    MYSQL_FIELD* fields;

    num_fields = mysql_num_fields(queryResult);
    fields = mysql_fetch_fields(queryResult);
    for (i = 0; i < num_fields; i++)
    {
        printf("Field %u is %s\n", i, fields[i].name);
        std::cout << "Field name: " << fields[i].name << std::endl;
        std::cout << "Field type: " << field_type_to_string(fields[i].type) << std::endl;
        std::cout << "Field allows NULL: " << ((fields[i].flags & NOT_NULL_FLAG) ? "No" : "Yes") << std::endl;
    }
    mysql_free_result(queryResult);
}

void BackDB::close()
{
    mysql_close(&mysql); // Close MySQL connection
}
//----------Basic Operations----------



//----------User----------

int BackDB::CountUser()
{
    QString queryStr = QString("SELECT COUNT(*) FROM users;");

    MYSQL_RES* queryResult = this->query(queryStr);


    if (mysql_num_rows(queryResult)==0 ||!queryResult) {
        std::cerr << "Query error occurred" << std::endl;
        return -1;
    }

    MYSQL_ROW row = mysql_fetch_row(queryResult);

    bool ok;
    QString qStr = row[0];
    int rowCount = qStr.toInt(&ok);

    mysql_free_result(queryResult);

    if (ok) {
        return rowCount;
    } else {
        std::cerr << "Error converting row count to int" << std::endl;
        return -1;
    }
}

//void BackDB::addUser(User _user) {
//    int id = _user.GetId();
//    QString name = _user.GetName();
//    QString password = _user.GetPassword();
//    int ranking = _user.GetRanking();
////    int value = _user.GetVIr().GetValue();
//    int value=64800;

//    QString queryStr = QString("INSERT INTO users (id, name, password, balance, ranking,user_time,introduction) "
//                               "VALUES ('%1', '%2', '%3',' %4',' %5','%6','%7')")
//                           .arg(id)
//                           .arg(name)
//                           .arg(password)
//                           .arg(value)
//                           .arg(ranking)
//                           .arg(1)
//                           .arg("INTRODUCTION NULL");
//    this->query(queryStr);
//}

//根据传入参数在数据库中添加新数据
//成功添加则返回true，否则返回false（避免用户名存在）
bool BackDB::addUser(QString name, QString password)
{
    qDebug()<<"Come to addUser"<<Qt::endl;
    if (isExist(name)) {
        std::cerr << "Error!!! User with name " << name.toStdString() << " already exists." << std::endl;
        return false;
    }

    int user_id=this->CountUser();

    QString queryStr = QString("INSERT INTO users (id, name, password, balance, ranking,user_time,introduction) "
                               "VALUES ('%1', '%2', '%3', '%4', '%5','%6','%7')")
                           .arg(user_id+1)
                           .arg(name)
                           .arg(password)
                           .arg(64800)
                           .arg(-1)
                           .arg(1)
                           .arg(0);

    this->query(queryStr);

    qDebug()<<"Come to end of addUser"<<Qt::endl;

    return true;
}

void BackDB::testUserAdd() {
    qDebug()<<"Test the UserAdd"<<Qt::endl;
    User u;
    this->addUser("HK-1","Hello");
}

bool BackDB::isExist(QString name)
{
    qDebug()<<"Come to isExist Function"<<Qt::endl;
    QString queryStr = QString("SELECT COUNT(*) FROM users WHERE name = '%1';")
                           .arg(name);

    MYSQL_RES* result = this->query(queryStr);

    MYSQL_ROW row = mysql_fetch_row(result);

    int count = atoi(row[0]); // Convert first column to integer

    qDebug()<<"Come to end of isExist Function"<<Qt::endl;

    return count > 0;
}

//根据用户名查找对应的密码，判断密码是否正确
//正确则返回true，错误返回false
bool BackDB::isPasswordEqual(QString name, QString password)
{
    qDebug()<<"Come to isPasswordEqual Function"<<Qt::endl;

    QString queryStr = QString("SELECT password FROM users WHERE name = '%1'")
                           .arg(name);

    MYSQL_RES* result = this->query(queryStr);
    if (result == nullptr) {
        std::cerr << "Query execution failed or result is null." << std::endl;
        return false;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    QString storedPassword = QString(row[0]);

    mysql_free_result(result);

    qDebug()<<"Come to end of isPasswordEqual Function"<<Qt::endl;

    return (storedPassword == password);
}

void BackDB::testIsPasswordEqual()
{
    QString name="LinFan";
    QString password="5201314";
    if(isPasswordEqual(name,password)==1)
    {
        qDebug()<<"Code right"<<Qt::endl;
    }
    else
    {
        qDebug()<<"Code wrong!!"<<Qt::endl;
    }
}

//根据用户名查找数据，并根据数据构建User，返回一个User
User BackDB::enableUser(QString name)
{
    QString queryStr = QString("SELECT * FROM users WHERE name = '%1'")
                           .arg(name);

    MYSQL_RES* result = this->query(queryStr);
    if (result == nullptr) {
        std::cerr << "Query execution failed or result is null." << std::endl;
        // Return a default or invalid User object
        return User();
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == nullptr) {
        std::cerr << "No user found with name " << name.toStdString() << std::endl;
        mysql_free_result(result);
        // Return a default or invalid User object
        return User();
    }

    else
    {
        int _id = atoi(row[0]);
        QString _name=row[1];
        QString _password=row[2];
        int _balance = atoi(row[3]);
        int _ranking = atoi(row[4]);
        User result(_id,_name,_password,_balance,_ranking);

        //        result.

        return result;
        //Return the coresponding data member
    }
}

void BackDB::testEnableUser()
{
    QString name="LinFan";
    User u=enableUser(name);
    qDebug()<<u.GetId()<<Qt::endl;
    qDebug()<<u.GetName()<<Qt::endl;
    qDebug()<<u.GetPassword()<<Qt::endl;
    qDebug()<<u.GetRanking()<<Qt::endl;
}

void BackDB::declineBalance(int id, int totalPrice)
{
    QString queryStr = QString("UPDATE users SET balance = balance - %1 WHERE id = %2;")
                           .arg(totalPrice)
                           .arg(id);
    this->query(queryStr);
}

void BackDB::inclineBalance(int id, int totalPrice)
{
    QString queryStr = QString("UPDATE users SET balance = balance + %1 WHERE id = %2;")
                           .arg(totalPrice)
                           .arg(id);
    this->query(queryStr);
}

void BackDB::testBalance()
{
    this->declineBalance(1,100);
}
int BackDB::getUserVolume(int userID, int companyID)
{
    QString queryStr = QString("SELECT volume FROM portfolios "
                               "WHERE  user_id= %1 AND company_id = %2;")
                           .arg(userID)
                           .arg(companyID);

    MYSQL_RES* queryResult=this->query(queryStr);




    if (mysql_num_rows(queryResult) == 0) { //此处绝对不能用==NULL进行判定
        return 0;
    }

    MYSQL_ROW row = mysql_fetch_row(queryResult);

    bool ok;
    QString qStr=row[0];
    long value = qStr.toLong(&ok);


    if(ok==1)
    {
        std::cout<<"Get volume:"<<value<<std::endl;
        return value;
    }
    else
    {
        return 0;
    }
}

int BackDB::GetBalance(int user_id)
{
    QString StrQuery = QString("SELECT balance FROM users WHERE id = %1;")
                           .arg(user_id);
    MYSQL_RES* queryResult=this->query(StrQuery);

    if (mysql_num_rows(queryResult) == 0) { //此处绝对不能用==NULL进行判定
        return 0;
    }

    MYSQL_ROW row = mysql_fetch_row(queryResult);

    bool ok;
    QString qStr=row[0];
    long value = qStr.toInt(&ok);


    if(ok==1)
    {
        std::cout<<"Get volume:"<<value<<std::endl;
        return value;
    }
    else
    {
        return 0;
    }

}

void BackDB::testGetBalance()
{
    std::cout<<this->GetBalance(0)<<std::endl;
}

//----------User----------



//----------Portfolios----------

void BackDB::addPortfolios(int user_id, int company_id, int volume) {
    QString queryStr = QString("INSERT INTO portfolios (user_id, company_id, volume) "
                               "VALUES (%1, %2, %3)")
                           .arg(user_id)
                           .arg(company_id)
                           .arg(volume);

     this->query(queryStr);
}

void BackDB::testPortfolios() {
     qDebug()<<"Test the Portfolios"<<Qt::endl;

     QRandomGenerator *generator = QRandomGenerator::global();

     // Generate a random integer between 0 and 100
    int user_id = generator->bounded(101);
    int company_id = 1;
    int volume = 1;
    this->addPortfolios(user_id, company_id, volume);
}

//----------Portfolios----------



//----------Record----------

void BackDB::addRecord(int _user_id, Record _record) {
    QString _date = _record.GetDate();
//    Stock _stock = _record.GetStock();

    int _company_id = _record.GetCompanyId();
    long _volume = _record.GetVolume();
    int _type = _record.GetTradeType();
    long _totalPrice = _record.GetTotalPrice();

    QString queryStr = QString("INSERT INTO trade_record (user_id, company_id, volume, date, trade_type, total_price) "
                               "VALUES (%1, %2, %3, '%4', %5, %6)")
                           .arg(_user_id)
                           .arg(_company_id)
                           .arg(_volume)
                           .arg(_date+"-30")
                           .arg(_type)
                           .arg(_totalPrice);

     this->query(queryStr);
}

void BackDB::testRecord() {
    Record _record;
    int user_id = 1; // Provide a valid user_id
    this->addRecord(user_id, _record);
}

//----------Records----------



//----------Tools----------

QString BackDB::Id2Name(int company_id)
{
    QStringList company_names = {
        "AAPL", "AMZN", "GOOGL", "IBM", "INTC",
        "JBLU", "META", "MSFT", "TSLA"
    };

    QString company_name;

    if (company_id >= 1 && company_id <= company_names.size()) {
        company_name = company_names[company_id - 1];
    } else {
        company_name = "Unknown";
    }

    qDebug() << "Selected company:" << company_name;

    return company_name;
}

//----------Tools----------



//----------Stocks----------

//每当切换BuyInStockBox的时候调用查询函数，传递参数为股票的companyId,年份，月份
//找到对应的股票
//返回一个长度为2的vector数组的引用，第一个为数字为股票价格,第二个数字为股票容量
//（暂时方案：如果股票价格不为整数则取整）
std::vector<long> &BackDB::getStockInfo(int id, int year, int month)
{
    QString name= Id2Name(id);

    QString queryStr = QString("SELECT CompanyName,(high + low) / 2 AS avg_price, \
                               volume  FROM  stock_data_monthly WHERE \
                               CompanyName = '%1' \
                               AND YEAR(`timestamp`) = %2 \
                                 AND MONTH(`timestamp`) = %3 \
                                   ")
                                       .arg(name)
                                       .arg(year)
                                       .arg(month);


//    this->showQuery(queryStr);
    std::vector<long>* ReturnVector=new std::vector<long>;

    MYSQL_RES* queryResult = query(queryStr);

    if (queryResult == NULL) {
        std::cerr << "Query failed: " << mysql_error(&mysql) << std::endl;
        return *ReturnVector;
    }

    unsigned int num_fields;
    unsigned int i;
    MYSQL_FIELD* fields;

    num_fields = mysql_num_fields(queryResult);

    MYSQL_ROW row = mysql_fetch_row(queryResult);

    std::cout << "Get the stock info:"<<row[0] << " "<<row[1]<<" "<<row[2]<<std::endl;

    bool ok;

    QString qStr_1=row[1];
    long value = (long)qStr_1.toDouble(&ok);
    std::cout << value << std::endl;


    QString qStr_2=row[2];
//    qDebug()<<qStr_2<<Qt::endl;
    unsigned long long volume = qStr_2.toLongLong(&ok);
    std::cout <<  volume << std::endl;

    if(ok==1)
    {
        ReturnVector->push_back(value);
        ReturnVector->push_back(volume);
    }
    else
    {
        std::cout<<"Error in Get StockInfo"<<std::endl;
    }

    mysql_free_result(queryResult);

    return *ReturnVector;
}


void BackDB::testGetStockInfo()
{
    std::vector<long> result=this->getStockInfo(8, 2023 ,2);
    std::cout<<"Get testGetStockInfo"<<std::endl;
    std::cout<<result[0]<<std::endl;
    std::cout<<result[1]<<std::endl;
}


void BackDB::AddStock(int userID, int company_id, int volume)
{
    long currentVolume = this->getUserVolume(userID, company_id);

    std::cout<<currentVolume<<std::endl;

    //1. 如果有这个股票
    if (currentVolume > 0) {

        QString updateQuery = QString("UPDATE portfolios SET volume = %1 WHERE user_id = %2 AND company_id = %3;")
                                  .arg(currentVolume + volume)
                                  .arg(userID)
                                  .arg(company_id);

        MYSQL_RES* updateResult = this->query(updateQuery);

        //        if (!updateResult) {
        //            std::cerr << "Update error occurred" << std::endl;
        //        } else {
        //            std::cout << "Volume updated successfully!" << std::endl;
        //        }
    }
    //2. 如果没有这个股票
    else {
        // Insert a new record
        QString insertQuery = QString("INSERT INTO portfolios (user_id, company_id, volume) VALUES (%1, %2, %3);")
                                  .arg(userID)
                                  .arg(company_id)
                                  .arg(volume);

        MYSQL_RES* insertResult = this->query(insertQuery);

        if (!insertResult) {
            std::cerr << "Insert error occurred" << std::endl;
        } else {
            std::cout << "New stock added successfully!" << std::endl;
        }
    }
}

//----------Stocks----------



//----------Records----------
//传入一个用户id，查询Record表中的数据，并根据这些数据构建一个Record的数组，并返回
std::vector<Record> &BackDB::getUserRecord(int userID)//----------------
{
    std::vector<Record>* ReturnRecord=new  std::vector<Record>;

    QString strQuery = QString("SELECT * FROM trade_record WHERE user_id = %1;")
                           .arg(userID);

    //    this->showQuery(queryResult);

    //     Record(QString _date, int _company_id, long _volume, bool _tradetype, long _totalprice);

    MYSQL_RES* queryResult = this->query(strQuery);

    if (mysql_num_rows(queryResult) == 0) { //此处绝对不能用==NULL进行判定
        std::cerr<<"Error: No UserRecord"<<std::endl;
        return *ReturnRecord;
    }

    //获取实际数据
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(queryResult))) {
        bool ok;

        QString qVolume(row[2]);
        long volume=qVolume.toLong(&ok);

        QString qType(row[4]);
        int _trade_type=qType.toInt(&ok);

        QString qTotalPrice(row[5]);
        long _total_price=qTotalPrice.toLong();

        QString qCompanyId(row[1]);
        int _CompanyId=qCompanyId.toInt(&ok);

        QString qDate(row[3]);
        qDebug()<<"Date:"<<qDate<<Qt::endl;//将日期输出
        //        double number = qStr.toDouble(&ok);

        Record item(qDate, _CompanyId,volume, _trade_type, _total_price);

        ReturnRecord->push_back(item);
    }


    return *ReturnRecord;
}


//----------Records----------



//----------Folios---------
//给传入一个用户id，查询portfolio表中该用户id对应的数据，并且构建一个根据这些数据构建好的Portfolio
//（或者你返回一个map回来我构建也行，map是portfolio里的那种map）
//即第一个int(key)代表公司/股票id，第二个代表持有数量(键值对）
Portfolio &BackDB::getUserPortfolio(int userID)//-------------
{


   std::map<int, int> myMap;

    QString strQuery = QString("SELECT * FROM portfolios WHERE user_id =%1;")
                           .arg(userID);

    MYSQL_RES* queryResult = this->query(strQuery);

    if (mysql_num_rows(queryResult) == 0) { //此处绝对不能用==NULL进行判定
        std::cerr<<"Error: No UserRecord"<<std::endl;
    }

    //获取实际数据
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(queryResult))) {
        bool ok;

        QString qVolume(row[2]);
        int volume=qVolume.toInt(&ok);


        QString qCompanyId(row[1]);
        int _CompanyId=qCompanyId.toInt(&ok);

        myMap.insert(std::make_pair(_CompanyId, volume));

    }

    Portfolio* p=new Portfolio(myMap);

    return* p;
}


void BackDB::testGetUserPortfolio()
{
    Portfolio test=this->getUserPortfolio(19);
    std::cout<<test.getHoldings(1314)<<std::endl;
}



void BackDB::addPost(Post post)
{
    int _date=post.getdate();
    QString _content=post.getcontent();
    QString _id=post.getid();
    int _father_id=post.getfatherid();
    int _this_id=post.getthisid();

    QString strQuery = QString("INSERT INTO forum(`Month`,user_id,COMMENT,father_id,this_id) \
                                VALUES ('%1','%2','%3','%4','%5');")
                           .arg(_date)
                           .arg(_id)
                           .arg(_content)
                           .arg(_father_id)
                           .arg(_this_id);
    this->query(strQuery);

}

void BackDB::RemoveStock(int userID, int company_id, int volume)
{
    long currentVolume = this->getUserVolume(userID, company_id);

    std::cout<<currentVolume<<std::endl;

    //1. 如果删除操作合理
    if (currentVolume >= volume) {

        QString updateQuery = QString("UPDATE portfolios SET volume = %1 WHERE user_id = %2 AND company_id = %3;")
                                  .arg(currentVolume - volume)
                                  .arg(userID)
                                  .arg(company_id);

        this->showQuery(updateQuery);

        std::cout<<"In the remove Stock"<<std::endl;

        //        if (!updateResult) {
        //            std::cerr << "Update error occurred" << std::endl;
        //        } else {
        //            std::cout << "Volume updated successfully!" << std::endl;
        //        }
    }
    //2. 如果股票含量不足
    else {
        std::cerr<<"Have no sufficient volume in Remove Stock"<<std::endl;
    }
}

std::vector<Post> BackDB::getforum()
{

    std::vector<Post> ReturnRecord;

    QString strQuery = QString("select * from forum;");
    MYSQL_RES* queryResult=this->query(strQuery);

    if (mysql_num_rows(queryResult) == 0) { //此处绝对不能用==NULL进行判定
        std::cerr<<"Error: No UserRecord"<<std::endl;
        return ReturnRecord;
    }

    //获取实际数据
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(queryResult))) {
        bool ok;

        QString qMonth(row[0]);
        int _date=qMonth.toInt(&ok);

        QString qUserId(row[1]);
//        int _user_id=qUserId.toInt(&ok);

        QString qComment(row[2]);
//        long _total_price=qTotalPrice.toLong();

        QString qFatherId(row[3]);
        int _father_id=qFatherId.toInt(&ok);

        QString qThisId(row[4]);
        int _this_id=qThisId.toInt(&ok);

        Post item(_date,
                  qComment,
                  qUserId,
                  _father_id,_this_id); //

//        Post(int _date,
//             QString _file,
//             QString _id,
//             int _fatherid,
//             int &_thisid = allnumber); //

        ReturnRecord.push_back(item);
    }
}

void BackDB::testAddPost()
{
    Post test(12,"Hello,Mr Lin","1",1);
    this->addPost(test);
}

void BackDB::testGetForum()
{
    std::vector<Post> resulr=this->getforum();
    for(int i=0;i<resulr.size();i++)
    {
        qDebug()<<resulr[i].getcontent()<<Qt::endl;
    }
}


std::map<int, std::vector<QString>>& BackDB::getNews(int _month)
{
    std::map<int,std::vector<QString>>* ReturnRecord=new std::map<int,std::vector<QString>>;

    QString strQuery = QString("SELECT month,content FROM news WHERE month <= %1")
                           .arg(_month);

    MYSQL_RES* queryResult=this->query(strQuery);
//    this->showQuery(strQuery);

    if (mysql_num_rows(queryResult) == 0) { //此处绝对不能用==NULL进行判定
        std::cerr<<"Error: No UserRecord"<<std::endl;
        return *ReturnRecord;
    }

    //获取实际数据
    MYSQL_ROW row;


    int i=1;
    std::vector<QString>* each=new  std::vector<QString>;

    while ((row = mysql_fetch_row(queryResult))) {

        //检测是否为下一个月,如果是下一个月，进行放入，然后新建一个新项
        bool ok;
        QString QstrMonth=row[0];
        int month=QstrMonth.toInt(&ok);

        if(month==i+1)
        {
            qDebug()<<"Add month "<<i+1<<Qt::endl;

            ReturnRecord->insert(std::make_pair(i, *each));
            std::vector<QString>* each=new  std::vector<QString>;
            i++;
        }

        QString content(row[1]);
        each->push_back(content);
    }

    ReturnRecord->insert(std::make_pair(i, *each));

    return *ReturnRecord;
    //此处不能delete，不然就会出错
}

void BackDB::setComment(int user_id, QString _comment)
{
    QString queryStr=QString("INSERT INTO comments_table \
                               (user_id,comment) VALUES \
                               ('%1','%2'); ")
                                   .arg(user_id)
                                   .arg(_comment);
                       this->query(queryStr);
}

void BackDB::setTime(int _userId, int month)
{
    QString queryStr=QString("UPDATE users \
                SET user_time = %1 \
                WHERE id = %2; \
                ")
                           .arg(month)
                           .arg(_userId);

                       this->query(queryStr);
}

int BackDB::getTime(int _userId)
{
                       QString queryStr=QString("SELECT * FROM users WHERE id=%1;")
                                              .arg(_userId);

                       MYSQL_RES* queryResult=this->query(queryStr);
                       //    this->showQuery(strQuery);

                       if (mysql_num_rows(queryResult) == 0) { //此处绝对不能用==NULL进行判定
        std::cerr<<"Error: No UserRecord"<<std::endl;
        return -1;
                       }

                       //获取实际数据
                       MYSQL_ROW row;
                       row=mysql_fetch_row(queryResult);

                       std::cout<<"GET MONTH:"<<row[5]<<std::endl;

                       bool ok;
                       QString StrMonth=row[5];
                       int _month=StrMonth.toInt(&ok);
                       if(ok)
        return _month;
                       else return -1;

}

void BackDB::setIntroduction(int _userId, QString _content)
{
    QString queryStr=QString("UPDATE users \
                SET introduction = '%1' \
                WHERE id = '%2'; \
                ")
                           .arg(_content)
                           .arg(_userId);

    this->query(queryStr);
}

void BackDB::setRanking(int _userId, int _ranking)
{
    QString queryStr=QString("UPDATE users \
                SET ranking = '%1' \
                WHERE id = '%2'; \
                ")
                           .arg(_ranking)
                           .arg(_userId);

    this->query(queryStr);
}


void BackDB::testGetNews()
{
    std::map<int, std::vector<QString>> test=this->getNews(12);
    qDebug()<<test[11].size()<<Qt::endl;
    for(int i=0;i<test[11].size();i++)
    {
        qDebug()<<test[11][i]<<Qt::endl;
    }
}

void BackDB::testGetUserRecord()
{
    std::vector<Record> RecordSet=this->getUserRecord(1);
    std::cout<<"SIZE:"<<RecordSet.size()<<std::endl;
    for(int i=0;i<RecordSet.size();i++) std::cout<<RecordSet[i].GetTotalPrice()<<std::endl;
}



void BackDB::testGetUserVolume()
{
    int ret=this->getUserVolume(22,13144);
    std::cout<<"testGetUserVolume: "<<ret<<std::endl;
}

void BackDB::testAddStock()
{
    this->RemoveStock(22,13144,100);
}

//----------test----------

void BackDB::test()
{
//    this->testGetNews();
    this->getTime(1);
    std::cout<<"Done in test"<<std::endl;
}






