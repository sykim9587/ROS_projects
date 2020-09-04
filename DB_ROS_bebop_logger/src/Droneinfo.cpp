#include "Droneinfo.h"
#include <string>
#include <iostream>
#include <stdlib.h>

DroneInfo::DroneInfo()
{
    this->droneId = 0;
    this->droneName = NULL;
    this->host = NULL;
    this->user = NULL;
    this->pw = NULL;
    this->port = 0;
    this->db = NULL;
}

DroneInfo::DroneInfo(int droneId, const char* droneName, const char* host, const char* user, 
    const char* pw, const char* db,int port)
{
    this->droneId = droneId;
    this->droneName = droneName;
    this->host = host;
    this->user = user;
    this->pw = pw;
    this->port = port;
    this->db = db;
}



DroneInfo::DroneInfo(const char* host, const char* user, const char* pw, const char* db,int port)
{
    this->host = host;
    this->user = user;
    this->pw = pw;
    this->port = port;
    this->db = db;
}

void DroneInfo::input_droneinfo()
{
    mysql_init(&this->conn);

    this->connection = mysql_real_connect(&this->conn, this->host, this->user, this->pw, this->db, this->port, (const char*)NULL, 0 ); 

    std::string query = "insert into DroneInfo values (" + std::to_string(this->droneId) + "," + "\"" + this->droneName + "\"" + ")";

    int state=0;
    state = mysql_query(connection, query.c_str()); //change to const char*

    if(state == 0)
        std::cout << "Complete" << std::endl;
    else
    {
        std::cout << "Error" << std::endl;
    }
    mysql_close(connection);

}

int DroneInfo::get_DroneID_byname(const char* droneName)
{
    mysql_init(&this->conn);
    this->connection = mysql_real_connect(&this->conn, this->host, this->user, this->pw,
    this->db, this->port, (const char*)NULL, 0);

    std::string query = "select DroneId from DroneInfo where DroneName = " + (std::string)"\"" +(std::string)droneName + (std::string)"\"";
    int state = 0;
    int droneId = 0;

    state = mysql_query(this->connection, query.c_str());
    if (state == 0)
    {
        this->sql_result = mysql_store_result(connection);
        if(sql_result->field_count > 1)
            std::cout<<"Duplicated Drone name" <<std::endl;
        else
        {
            while((sql_row = mysql_fetch_row(sql_result)) != NULL)
                for(int i = 0; i<sql_result->field_count ; i++)
                    droneId = atoi(sql_row[i]);
        }
        
    }
    return droneId;    
}