#ifndef _USERCOMMENT_DAO_BASE_IMPL_H_
#define _USERCOMMENT_DAO_BASE_IMPL_H_
#include "Dao/UserCommentDao.h"
#include "framework/db/dbpublic.h"
#include "framework/db/dao/daobase.h"
namespace Dao
{
    namespace Impl
    {
        class CUserCommentCached;
        class CUserCommentDaoImplBase
                :public Dao::IUserCommentDao,
                public cdf::dao::CDaoBase
        {
        public:
            CUserCommentDaoImplBase();
            virtual ~CUserCommentDaoImplBase();
            virtual bool get( int id , Message::Db::Tables::TUserComment& v , bool update = false );
            virtual void save( Message::Db::Tables::TUserComment& v );
            virtual bool update( const Message::Db::Tables::TUserComment& v );
            virtual bool remove( int id );
            
            virtual long64_t find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUserComment& v , bool update = false );
            virtual bool find( const cdf::dao::SQuery& query , Message::Db::Tables::TUserComment& v , bool update = false );
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUserComment& v);
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq );
            virtual long64_t remove( const cdf::dao::SeqCmpNode& cmp );
            
            virtual bool get( int id , Message::Db::Tables::TUserComment& v , cdf::CStatement* stmt , bool update = false , bool usedCached = true );
            virtual void save( Message::Db::Tables::TUserComment& v , cdf::CStatement* stmt , bool usedCached = true );
            virtual bool update( const Message::Db::Tables::TUserComment& v , cdf::CStatement* stmt , bool usedCached = true );
            virtual bool remove( int id , cdf::CStatement* stmt , bool usedCached = true );
            
            virtual long64_t find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUserComment& v , cdf::CStatement* stmt , bool update = false , bool usedCached = true );
            virtual bool find( const cdf::dao::SQuery& query , Message::Db::Tables::TUserComment& v , cdf::CStatement* stmt , bool update = false , bool usedCached = true );
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUserComment& v, cdf::CStatement* stmt , bool usedCached = true );
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq , cdf::CStatement* stmt , bool usedCached = true );
            virtual long64_t remove( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt , bool usedCached = true );
            CUserCommentCached* getCached();
            
            
        public:
            const static int _columnCount;
            const static std::string _selectBase;
            const static std::string _updateBase;
            const static std::string _insertBase;
            const static std::string _deleteBase;
            void static __readTUserComment( Message::Db::Tables::TUserComment& outV , cdf::CResultSet* rs );
            void static __writeTUserComment( const Message::Db::Tables::TUserComment& outV , cdf::CStatement* stmt );
        
        private:
            CUserCommentCached *_cached;
            
        };
    }
}
#endif
