#ifndef _USER_DAO_BASE_IMPL_H_
#define _USER_DAO_BASE_IMPL_H_
#include "Dao/UserDao.h"
#include "framework/db/dbpublic.h"
#include "framework/db/dao/daobase.h"
namespace Dao
{
    namespace Impl
    {
        class CUserCached;
        class CUserDaoImplBase
                :public Dao::IUserDao,
                public cdf::dao::CDaoBase
        {
        public:
            CUserDaoImplBase();
            virtual ~CUserDaoImplBase();
            virtual bool get( int id , Message::Db::Tables::TUser& v , bool update = false );
            virtual void save( Message::Db::Tables::TUser& v );
            virtual bool update( const Message::Db::Tables::TUser& v );
            virtual bool remove( int id );
            
            virtual long64_t find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUser& v , bool update = false );
            virtual bool find( const cdf::dao::SQuery& query , Message::Db::Tables::TUser& v , bool update = false );
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUser& v);
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq );
            virtual long64_t remove( const cdf::dao::SeqCmpNode& cmp );
            
            virtual bool get( int id , Message::Db::Tables::TUser& v , cdf::CStatement* stmt , bool update = false , bool usedCached = true );
            virtual void save( Message::Db::Tables::TUser& v , cdf::CStatement* stmt , bool usedCached = true );
            virtual bool update( const Message::Db::Tables::TUser& v , cdf::CStatement* stmt , bool usedCached = true );
            virtual bool remove( int id , cdf::CStatement* stmt , bool usedCached = true );
            
            virtual long64_t find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUser& v , cdf::CStatement* stmt , bool update = false , bool usedCached = true );
            virtual bool find( const cdf::dao::SQuery& query , Message::Db::Tables::TUser& v , cdf::CStatement* stmt , bool update = false , bool usedCached = true );
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUser& v, cdf::CStatement* stmt , bool usedCached = true );
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq , cdf::CStatement* stmt , bool usedCached = true );
            virtual long64_t remove( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt , bool usedCached = true );
            CUserCached* getCached();
            
            
        public:
            const static int _columnCount;
            const static std::string _selectBase;
            const static std::string _updateBase;
            const static std::string _insertBase;
            const static std::string _deleteBase;
            void static __readTUser( Message::Db::Tables::TUser& outV , cdf::CResultSet* rs );
            void static __writeTUser( const Message::Db::Tables::TUser& outV , cdf::CStatement* stmt );
        
        private:
            CUserCached *_cached;
            
        };
    }
}
#endif
