#ifndef OOP_SRC_MYSQL_QUERY_H_
#define OOP_SRC_MYSQL_QUERY_H_

#ifndef MYSQLPP_MYSQL_HEADERS_BURIED
#define MYSQLPP_MYSQL_HEADERS_BURIED
#endif

#include "Connection.h"
#include <mysql++/mysql++.h>

#include <string>

namespace OOP_MYSQL
{
    typedef mysqlpp::Row Tuple;
    typedef mysqlpp::UseQueryResult Result;
    typedef mysqlpp::BadQuery QueryErr;
    typedef mysqlpp::ConnectionFailed ConnectionErr;
    
    enum Symbol
    {
        QUOTE,
        SUBSTRING
    };
    
    class Query
    {
    public:
        Query(const mysqlpp::Query& query);
        Query(Connection& conn, const char* queryStr);
        Query(const Query& other);
    
    public:
        virtual bool exec() = 0;
        
        bool isExecuted()
        {
            return executed;
        }
        
        unsigned long long affectedRows()
        {
            return query.affected_rows();
        }
        
        const mysqlpp::Query& getQuery() const
        {
            return query;
        }
        
        mysqlpp::Query& getQuery()
        {
            return query;
        }
        
        Query& operator<<(const std::string& str);
        Query& operator<<(const char* str);
        Query& operator<<(const Symbol& symbol);
 
    protected:
        bool executed;
    
    private:
        mysqlpp::Query query;
        bool needQuote;
        bool needSub;
    };
}

#endif
