#ifndef BEBOP_DRONEINFO_H
#define BEBOP_DRONEINFO_H

#include <mysql/mysql.h>

class DroneInfo
{
private:
    int droneId;
    const char* droneName;

    const char* host;
    const char* user;
    const char* pw;
    const char* db;
    int port;

    MYSQL* connection;
    MYSQL conn;
    MYSQL_RES* sql_result;
    MYSQL_ROW sql_row;
    MYSQL_FIELD sql_field;

public:
    DroneInfo(int droneId, const char* droneName, const char* host, const char* user, 
     const char* pw, const char* db,int port);
    DroneInfo(const char* host, const char* user, const char* pw, const char* db,int port);
    DroneInfo();
    void input_droneinfo();
    int get_DroneID_byname(const char* droneName);
    



};

#endif