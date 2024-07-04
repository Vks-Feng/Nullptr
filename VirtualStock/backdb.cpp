#include "backdb.h"
#include "QString"
#include <string>
#include <QDebug>
#include "user.h"
#include "record.h"
#include "portfolio.h"
#include "stock.h"


// The implement of backEndWithDataBase Class

//Constructor , the basic information is host+user+password+database
BackDB::BackDB(const char* _host, const  char* _user, const  char* _password, const  char* _database,
                                         unsigned int _port, const char* _unix_socket , unsigned long _client_flag)
    :host(_host), user(_user), password(_password), database(_database), port(_port), unix_socket(_unix_socket)
    , client_flag(_client_flag)
{
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

//Return the MYSQL_RES Pointer of the return result
MYSQL_RES* BackDB::query(const char* query)
{
    // Assuming 'mysql' is already initialized and connected properly

    int ret = mysql_query(&mysql, query);

    //If the query cannot perform well
    if (ret != 0) {
        std::cout << "Query execution failed: " << mysql_error(&mysql) << std::endl;
        return nullptr;
    }

    //If perform well
    else {
        // Query executed successfully, handle results
        MYSQL_RES* result = mysql_store_result(&mysql);

        //If the result set is NULL
         if (result == nullptr) {
            std::cout << "Failed to get the result set" << std::endl;
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
        std::cout << "Query execution failed: " << mysql_error(&mysql) << std::endl;
        StringReturn = "Query execution failed:";
        return StringReturn;
    }
    else {
        // Query executed successfully, handle results
        MYSQL_RES* result = mysql_store_result(&mysql);

        if (result == nullptr) {
            std::cout << "Failed to get the result set" << std::endl;
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

//---------------------

void BackDB::addUser(User _user) {
    int id = _user.GetId();
    QString name = _user.GetName();
    QString password = _user.GetPassword();
    int ranking = _user.GetRanking();
//    int value = _user.GetVIr().GetValue();
    int value=-1;

    QString queryStr = QString("INSERT INTO users (id, name, password, balance, ranking) "
                               "VALUES (%1, '%2', '%3', %4, %5)")
                           .arg(id)
                           .arg(name)
                           .arg(password)
                           .arg(value)
                           .arg(ranking);

    this->query(queryStr);
}

//根据传入参数在数据库中添加新数据
//成功添加则返回true，否则返回false（避免用户名存在）
bool BackDB::addUser(QString name, QString password)
{
       qDebug()<<"Come to here"<<Qt::endl;
    if (isExist(name)) {
        std::cout << "Error!!! User with name " << name.toStdString() << " already exists." << std::endl;
        return false;
    }

   qDebug()<<"Come to here to register the user "+name<<Qt::endl;

    QString queryStr = QString("INSERT INTO users (id, name, password, balance, ranking) "
                               "VALUES (%1, '%2', '%3', %4, %5)")
                           .arg(1)
                           .arg(name)
                           .arg(password)
                           .arg(648)
                           .arg(-1);

    qDebug()<<"Come to here"<<Qt::endl;

    if (this->query(queryStr) != nullptr)
    {
        qDebug()<<"Succeed in creating user "+name<<Qt::endl;
        return true;
    }
    else
    {
        qDebug()<<"Fail in creating user "+name<<Qt::endl;
        return false;
    }
}

void BackDB::testUserAdd() {
    qDebug()<<"Test the UserAdd"<<Qt::endl;
    User u;
//    this->addUser(u);
    this->addUser("Helg","Hello");
}

//------------------------

void BackDB::addPortfolios(int user_id, int company_id, int volume) {
    QString queryStr = QString("INSERT INTO portfolios (user_id, company_id, volumn) "
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

//-----------------------

void BackDB::addRecord(int _user_id, Record _record) {
    QString _date = _record.GetDate();
    Stock _stock = _record.GetStock();
    int _company_id = _stock.GetCompanyId();
    long _volume = _record.GetVolume();
    int _type = _record.GetTradeType();
    long _totalPrice = _record.GetTotalPrice();

    QString queryStr = QString("INSERT INTO trade_record (user_id, company_id, volumn, date, trade_type, total_price) "
                               "VALUES (%1, %2, %3, '%4', %5, %6)")
                           .arg(_user_id)
                           .arg(_company_id)
                           .arg(_volume)
                           .arg(_date)
                           .arg(_type)
                           .arg(_totalPrice);

     this->query(queryStr);
}

void BackDB::testRecord() {
    Record _record;
    int user_id = 1; // Provide a valid user_id
    this->addRecord(user_id, _record);
}


//------------------------
//Cloase the Mysql
void BackDB::close()
{
    mysql_close(&mysql); // Close MySQL connection
}

bool BackDB::isExist(QString name)
{
    qDebug()<<"Come to isExist1"<<Qt::endl;
    QString queryStr = QString("SELECT COUNT(*) FROM users WHERE name = '%1';")
                           .arg(name);

    qDebug()<<"Come to isExist2"<<Qt::endl;

    MYSQL_RES* result = this->query(queryStr);


     qDebug()<<"Come to isExist3"<<Qt::endl;



     qDebug()<<"Come to isExist4"<<Qt::endl;

    MYSQL_ROW row = mysql_fetch_row(result);

     qDebug()<<"Come to isExist4.1"<<Qt::endl;


     int count = atoi(row[0]); // Convert first column to integer

    qDebug()<<"Come to isExist4.5"<<Qt::endl;


    return count > 0;
}



//根据用户名查找对应的密码，判断密码是否正确
//正确则返回true，错误返回false
bool BackDB::isPasswordEqual(QString name, QString password)
{
    QString queryStr = QString("SELECT password FROM users WHERE name = '%1'")
                           .arg(name);

    MYSQL_RES* result = this->query(queryStr);
    if (result == nullptr) {
        std::cout << "Query execution failed or result is null." << std::endl;
        return false;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    QString storedPassword = QString(row[0]);

    mysql_free_result(result);

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
        std::cout << "Query execution failed or result is null." << std::endl;
        // Return a default or invalid User object
        return User();
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == nullptr) {
        std::cout << "No user found with name " << name.toStdString() << std::endl;
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






