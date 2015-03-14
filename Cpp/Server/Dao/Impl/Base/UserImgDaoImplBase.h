#ifndef _USERIMG_DAO_BASE_IMPL_H_
#define _USERIMG_DAO_BASE_IMPL_H_
#include "Dao/UserImgDao.h"
#include "framework/db/dbpublic.h"
#include "framework/db/dao/daobase.h"
namespace Dao
{
    namespace Impl
    {
        class CUserImgCached;
        class CUserImgDaoImplBase
                :public Dao::IUserImgDao,
                public cdf::dao::CDaoBase
        {
        public:
            CUserImgDaoImplBase();
            virtual ~CUserImgDaoImplBase();
            virtual bool get( int id , Message::Db::Tables::TUserImg& v , bool update = false );
            virtual void save( Message::Db::Tables::TUserImg& v );
            virtual bool update( const Message::Db::Tables::TUserImg& v );
            virtual bool remove( int id );
            
            virtual long64_t find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUserImg& v , bool update = false );
            virtual bool find( const cdf::dao::SQuery& query , Message::Db::Tables::TUserImg& v , bool update = false );
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUserImg& v);
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq );
            virtual long64_t remove( const cdf::dao::SeqCmpNode& cmp );
            
            virtual bool get( int id , Message::Db::Tables::TUserImg& v , cdf::CStatement* stmt , bool update = false , bool usedCached = true );
            virtual void save( Message::Db::Tables::TUserImg& v , cdf::CStatement* stmt , bool usedCached = true );
            virtual bool update( const Message::Db::Tables::TUserImg& v , cdf::CStatement* stmt , bool usedCached = true );
            virtual bool remove( int id , cdf::CStatement* stmt , bool usedCached = true );
            
            virtual long64_t find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUserImg& v , cdf::CStatement* stmt , bool update = false , bool usedCached = true );
            virtual bool find( const cdf::dao::SQuery& query , Message::Db::Tables::TUserImg& v , cdf::CStatement* stmt , bool update = false , bool usedCached = true );
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUserImg& v, cdf::CStatement* stmt , bool usedCached = true );
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq , cdf::CStatement* stmt , bool usedCached = true );
            virtual long64_t remove( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt , bool usedCached = true );
            CUserImgCached* getCached();
            
            
        public:
            const static int _columnCount;
            const static std::string _selectBase;
            const static std::string _updateBase;
            const static std::string _insertBase;
            const static std::string _deleteBase;
            void static __readTUserImg( Message::Db::Tables::TUserImg& outV , cdf::CResultSet* rs );
            void static __writeTUserImg( const Message::Db::Tables::TUserImg& outV , cdf::CStatement* stmt );
        
        private:
            CUserImgCached *_cached;
            
        };
    }
}
#endif
