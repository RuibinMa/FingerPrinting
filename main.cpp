
#include <iostream>
#include <sqlite3.h>
#include <string>

int callback(void *NotUsed, int argc, char **argv, char **azColName);

int main()
{
    std::cout<<sqlite3_libversion()<<std::endl;

	sqlite3 *db;
    char *err_msg = 0;

    const char * path_to_database = "database.db";

    int rc = sqlite3_open(path_to_database, &db);
    if(rc != SQLITE_OK){
        std::cerr<<"Cannot open database: "<<sqlite3_errmsg(db)<<std::endl;
        sqlite3_close(db);
        return 1;
    }

    const char *sql = "SELECT * FROM images;";
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    if(rc != SQLITE_OK){
        std::cerr<<"Failed to fetch data: "<<sqlite3_errmsg(db)<<std::endl;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);

	return 0;
}
int callback(void *, int argc, char** argv, char** azColName)
{
    for(int i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : NULL);
    }
    std::cout<<std::endl;
    return 0;
}
