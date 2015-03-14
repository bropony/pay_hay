#ifndef _USERPOST_DAO_BASE_IMPL_H_
#define _USERPOST_DAO_BASE_IMPL_H_
#include "Dao/UserPostDao.h"
#include "framework/db/dbpublic.h"
#include "framework/db/dao/daobase.h"
namespace Dao
{
    namespace Impl
    {
        class CUserPostCached;
        class CUserPostDaoImplBase
                :public Dao::IUserPostDao,
                public cdf::dao::CDaoBase
        {
        public:
            CUserPostDaoImplBase();
            virtual ~CUserPostDaoImplBase();
            virtual bool get( int id , Message::Db::Tables::TUserPost& v , bool update = false );
            virtual void save( Message::Db::Tables::TUserPost& v );
            virtual bool update( const Message::Db::Tables::TUserPost& v );
            virtual bool remove( int id );
            
            virtual long64_t find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUserPost& v , bool update = false );
            virtual bool find( const cdf::dao::SQuery& query , Message::Db::Tables::TUserPost& v , bool update = false );
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUserPost& v);
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq );
            virtual long64_t remove( const cdf::dao::SeqCmpNode& cmp );
            
            virtual bool get( int id , Message::Db::Tables::TUserPost& v , cdf::CStatement* stmt , bool update = false , bool usedCached = true );
            virtual void save( Message::Db::Tables::TUserPost& v , cdf::CStatement* stmt , bool usedCached = true );
            virtual bool update( const Message::Db::Tables::TUserPost& v , cdf::CStatement* stmt , bool usedCached = true );
            virtual bool remove( int id , cdf::CStatement* stmt , bool usedCached = true );
            
            virtual long64_t find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUserPost& v , cdf::CStatement* stmt , bool update = false , bool usedCached = true );
            virtual bool find( const cdf::dao::SQuery& query , Message::Db::Tables::TUserPost& v , cdf::CStatement* stmt , bool update = false , bool usedCached = true );
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUserPost& v, cdf::CStatement* stmt , bool usedCached = true );
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq , cdf::CStatement* stmt , bool usedCached = true );
            virtual long64_t remove( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt , bool usedCached = true );
            CUserPostCached* getCached();
            
            
        public:
            const static int _columnCount;
            const static std::string _selectBase;
            const static std::string _updateBase;
            const static std::string _insertBase;
            const static std::string _deleteBase;
            void static __readTUserPost( Message::Db::Tables::TUserPost& outV , cdf::CResultSet* rs );
            void static __writeTUserPost( const Message::Db::Tables::TUserPost& outV , cdf::CStatement* stmt );
        
        private:
            CUserPostCached *_cached;
            
        };
    }
}
#endif
