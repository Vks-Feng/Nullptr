#include "backEndWithDataBase2.h"

// Constructor: initializes the database connection
backEndWithDataBase2::backEndWithDataBase(const QString& host, const QString& user, const QString& password, const QString& database,
                                         int port, const QString& connectionName)
{
    db = QSqlDatabase::addDatabase("QMYSQL", connectionName);
    db.setHostName(host);
    db.setUserName(user);
    db.setPassword(password);
    db.setDatabaseName(database);
    db.setPort(port);

    if (!db.open()) {
        std::cerr << "Failed to connect to database: " << db.lastError().text().toStdString() << std::endl;
    } else {
        std::cout << "Database connection successful!" << std::endl;
    }
}

// Executes a query and returns the result set
QSqlQuery backEndWithDataBase2::query(const QString& queryStr)
{
    QSqlQuery query(db);
    if (!query.exec(queryStr)) {
        std::cerr << "Query execution failed: " << query.lastError().text().toStdString() << std::endl;
    }
    return query;
}

// Prints the table description
void backEndWithDataBase2::tableDesc(const QString& tableName)
{
    QString queryString = QString("DESCRIBE %1").arg(tableName);
    QSqlQuery query = this->query(queryString);

    if (!query.isActive()) {
        std::cerr << "Failed to describe table: " << query.lastError().text().toStdString() << std::endl;
        return;
    }

    while (query.next()) {
        QString field = query.value("Field").toString();
        QString type = query.value("Type").toString();
        QString nullAllowed = query.value("Null").toString();

        std::cout << "Field: " << field.toStdString() << ", Type: " << type.toStdString()
                  << ", Allows NULL: " << nullAllowed.toStdString() << std::endl;
    }
}

// Closes the database connection
void backEndWithDataBase2::close()
{
    db.close();
}
