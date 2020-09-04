#include "status.h"
#include "time.h"
#include "string"

Status::Status(const char* host, const char* user, const char* pw, const char* db, int port)
{
    this->host = host;
    this->user = user;
    this->pw = pw;
    this->db = db;
    this->port = port;
}

Status::Status()
{
    this->host = NULL;
    this->user = NULL;
    this->pw = NULL;
    this->db = NULL;
    this->port = NULL;
}

void Status::insert_status(int statusId, int droneId, double latitude, double longitude, double altitude, int batteryPercent)
{
    time_t t = time(NULL);
    struct tm curr_tm = *localtime(&t);

    int year = curr_tm.tm_year + 1900;
    int month = curr_tm.tm_mon + 1;
    int day = curr_tm.tm_mday;
    int hour = curr_tm.tm_hour;
    int min = curr_tm.tm_min;
    int sec = curr_tm.tm_sec;

    this->timeStamp = std::to_string(year)+ "-" + std::to_string(month) + "-" +
    std::to_string(day) + " " + std::to_string(hour)+":"+std::to_string(min)+":"+std::to_string(sec);

    mysql_init(&this->conn);
    this->connect = mysql_real_connect(&this->conn, this->host, this->user, this->pw, this->db, this->port, (const char*)NULL, 0 ); 
    if(this->connect == NULL)
        std::cout << "not connected "<<std::endl;

    std::string query = "insert into Status value(" +std::to_string(statusId) +
    ","+ std::to_string(droneId) + "," + "\"" + timeStamp+ "\"" + "," + std::to_string(latitude) + "," + std::to_string(longitude)  + "," + std::to_string(altitude)  + ","
    + std::to_string(batteryPercent)+ ")";

    std::cout << query << std::endl;

    int state = 0;
    state = mysql_query(this->connect, query.c_str());
    std::cout << state << std::endl;

    if(state == 0)
        std::cout << "status Complete" << std::endl;
    else
    {
        std::cout << "status Error" << std::endl;
    }
    mysql_close(connect);

    //status ID should be updated. 

}