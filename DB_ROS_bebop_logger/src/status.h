#ifndef BEBOP_STATUS_H
#define BEPOP_STATUS_H

#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <stdlib.h>

class Status
{
private:
    int statusId;
    int droneId;
    std::string timeStamp;
    double latitude;
    double longitude;
    double altitude; 
    int batteryPercent;

    MYSQL* connect;
    MYSQL conn;
    MYSQL_RES *sql_result;
    MYSQL_ROW sql_row;
    MYSQL_FIELD sql_field;

    const char* host;
    const char* user;
    const char* db;
    const char* pw;
    int port;


public:
    Status(const char* host, const char* user, const char* pw, const char* db, int port);
    void insert_status(int statusId, int droneId, double latitude, double longitude, double altitude, int batteryPercent);   
    Status();
};

#endif