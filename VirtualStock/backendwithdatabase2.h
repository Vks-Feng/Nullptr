#pragma once

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <iostream>

class backEndWithDataBase2
{
private:
    QSqlDatabase db;

public:
    // Constructor: initializes the database connection
    backEndWithDataBase(const QString& host, const QString& user, const QString& password, const QString& database,
                        int port = 3306, const QString& connectionName = "default");

    // Executes a query and returns the result set
    QSqlQuery query(const QString& queryStr);

    // Prints the table description
    void tableDesc(const QString& tableName);

    // Closes the database connection
    void close();
};
